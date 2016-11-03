.. comment SPDX-License-Identifier: CC-BY-SA-4.0

.. COMMENT: COPYRIGHT (c) 1988-2008.
.. COMMENT: On-Line Applications Research Corporation (OAR).
.. COMMENT: All rights reserved.

Key Concepts
############

Introduction
============

The facilities provided by RTEMS are built upon a foundation of very powerful
concepts.  These concepts must be understood before the application developer
can efficiently utilize RTEMS.  The purpose of this chapter is to familiarize
one with these concepts.

.. _objects:

Objects
=======

.. index:: objects

RTEMS provides directives which can be used to dynamically create, delete, and
manipulate a set of predefined object types.  These types include tasks,
message queues, semaphores, memory regions, memory partitions, timers, ports,
and rate monotonic periods.  The object-oriented nature of RTEMS encourages the
creation of modular applications built upon re-usable "building block"
routines.

All objects are created on the local node as required by the application and
have an RTEMS assigned ID.  All objects have a user-assigned name.  Although a
relationship exists between an object's name and its RTEMS assigned ID, the
name and ID are not identical.  Object names are completely arbitrary and
selected by the user as a meaningful "tag" which may commonly reflect the
object's use in the application.  Conversely, object IDs are designed to
facilitate efficient object manipulation by the executive.

Object Names
------------
.. index:: object name
.. index:: rtems_name

An object name is an unsigned thirty-two bit entity associated with the object
by the user.  The data type ``rtems_name`` is used to store object
names... index:: rtems_build_name

Although not required by RTEMS, object names are often composed of four ASCII
characters which help identify that object.  For example, a task which causes a
light to blink might be called "LITE".  The ``rtems_build_name`` routine is
provided to build an object name from four ASCII characters.  The following
example illustrates this:

.. code-block:: c

    rtems_name my_name;
    my_name = rtems_build_name( 'L', 'I', 'T', 'E' );

However, it is not required that the application use ASCII characters to build
object names.  For example, if an application requires one-hundred tasks, it
would be difficult to assign meaningful ASCII names to each task.  A more
convenient approach would be to name them the binary values one through
one-hundred, respectively.

.. index:: rtems_object_get_name

RTEMS provides a helper routine, ``rtems_object_get_name``, which can be used
to obtain the name of any RTEMS object using just its ID.  This routine
attempts to convert the name into a printable string.

The following example illustrates the use of this method to print an object
name:

.. code-block:: c

    #include <rtems.h>
    #include <rtems/bspIo.h>
    void print_name(rtems_id id)
    {
        char  buffer[10];   /* name assumed to be 10 characters or less */
        char *result;
        result = rtems_object_get_name( id, sizeof(buffer), buffer );
        printk( "ID=0x%08x name=%s\n", id, ((result) ? result : "no name") );
    }

Object IDs
----------
.. index:: object ID
.. index:: object ID composition
.. index:: rtems_id

An object ID is a unique unsigned integer value which uniquely identifies an
object instance.  Object IDs are passed as arguments to many directives in
RTEMS and RTEMS translates the ID to an internal object pointer. The efficient
manipulation of object IDs is critical to the performance of RTEMS services.
Because of this, there are two object Id formats defined.  Each target
architecture specifies which format it will use.  There is a thirty-two bit
format which is used for most of the supported architectures and supports
multiprocessor configurations.  There is also a simpler sixteen bit format
which is appropriate for smaller target architectures and does not support
multiprocessor configurations.

Thirty-Two Object ID Format
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The thirty-two bit format for an object ID is composed of four parts: API,
object class, node, and index.  The data type ``rtems_id`` is used to store
object IDs.

.. code-block:: c

    31      27 26   24 23          16 15                             0
    +---------+-------+--------------+-------------------------------+
    |         |       |              |                               |
    |  Class  |  API  |     Node     |             Index             |
    |         |       |              |                               |
    +---------+-------+--------------+-------------------------------+

The most significant five bits are the object class.  The next three bits
indicate the API to which the object class belongs.  The next eight bits
(16-23) are the number of the node on which this object was created.  The node
number is always one (1) in a single processor system.  The least significant
sixteen bits form an identifier within a particular object type.  This
identifier, called the object index, ranges in value from 1 to the maximum
number of objects configured for this object type.

Sixteen Bit Object ID Format
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The sixteen bit format for an object ID is composed of three parts: API, object
class, and index.  The data type ``rtems_id`` is used to store object IDs.

.. code-block:: c

    15      11 10    8 7            0
    +---------+-------+--------------+
    |         |       |              |
    |  Class  |  API  |    Index     |
    |         |       |              |
    +---------+-------+--------------+

The sixteen-bit format is designed to be as similar as possible to the
thrity-two bit format.  The differences are limited to the eliminatation of the
node field and reduction of the index field from sixteen-bits to 8-bits.  Thus
the sixteen bit format only supports up to 255 object instances per API/Class
combination and single processor systems.  As this format is typically utilized
by sixteen-bit processors with limited address space, this is more than enough
object instances.

Object ID Description
---------------------

The components of an object ID make it possible to quickly locate any object in
even the most complicated multiprocessor system.  Object ID's are associated
with an object by RTEMS when the object is created and the corresponding ID is
returned by the appropriate object create directive.  The object ID is required
as input to all directives involving objects, except those which create an
object or obtain the ID of an object.

The object identification directives can be used to dynamically obtain a
particular object's ID given its name.  This mapping is accomplished by
searching the name table associated with this object type.  If the name is
non-unique, then the ID associated with the first occurrence of the name will
be returned to the application.  Since object IDs are returned when the object
is created, the object identification directives are not necessary in a
properly designed single processor application.

In addition, services are provided to portably examine the subcomponents of an
RTEMS ID.  These services are described in detail later in this manual but are
prototyped as follows:

.. index:: obtaining class from object ID
.. index:: obtaining node from object ID
.. index:: obtaining index from object ID
.. index:: get class from object ID
.. index:: get node from object ID
.. index:: get index from object ID
.. index:: rtems_object_id_get_api
.. index:: rtems_object_id_get_class
.. index:: rtems_object_id_get_node
.. index:: rtems_object_id_get_index

.. code-block:: c

    uint32_t rtems_object_id_get_api( rtems_id );
    uint32_t rtems_object_id_get_class( rtems_id );
    uint32_t rtems_object_id_get_node( rtems_id );
    uint32_t rtems_object_id_get_index( rtems_id );

An object control block is a data structure defined by RTEMS which contains the
information necessary to manage a particular object type.  For efficiency
reasons, the format of each object type's control block is different.  However,
many of the fields are similar in function.  The number of each type of control
block is application dependent and determined by the values specified in the
user's Configuration Table.  An object control block is allocated at object
create time and freed when the object is deleted.  With the exception of user
extension routines, object control blocks are not directly manipulated by user
applications.

Communication and Synchronization
=================================
.. index:: communication and synchronization

In real-time multitasking applications, the ability for cooperating execution
threads to communicate and synchronize with each other is imperative.  A
real-time executive should provide an application with the following
capabilities:

- Data transfer between cooperating tasks

- Data transfer between tasks and ISRs

- Synchronization of cooperating tasks

- Synchronization of tasks and ISRs

Most RTEMS managers can be used to provide some form of communication and/or
synchronization.  However, managers dedicated specifically to communication and
synchronization provide well established mechanisms which directly map to the
application's varying needs.  This level of flexibility allows the application
designer to match the features of a particular manager with the complexity of
communication and synchronization required.  The following managers were
specifically designed for communication and synchronization:

- Semaphore

- Message Queue

- Event

- Signal

The semaphore manager supports mutual exclusion involving the synchronization
of access to one or more shared user resources.  Binary semaphores may utilize
the optional priority inheritance algorithm to avoid the problem of priority
inversion.  The message manager supports both communication and
synchronization, while the event manager primarily provides a high performance
synchronization mechanism.  The signal manager supports only asynchronous
communication and is typically used for exception handling.

Time
====
.. index:: time

The development of responsive real-time applications requires an understanding
of how RTEMS maintains and supports time-related operations.  The basic unit of
time in RTEMS is known as a tick.  The frequency of clock ticks is completely
application dependent and determines the granularity and accuracy of all
interval and calendar time operations.

.. index:: rtems_interval

By tracking time in units of ticks, RTEMS is capable of supporting interval
timing functions such as task delays, timeouts, timeslicing, the delayed
execution of timer service routines, and the rate monotonic scheduling of
tasks.  An interval is defined as a number of ticks relative to the current
time.  For example, when a task delays for an interval of ten ticks, it is
implied that the task will not execute until ten clock ticks have occurred.
All intervals are specified using data type ``rtems_interval``.

A characteristic of interval timing is that the actual interval period may be a
fraction of a tick less than the interval requested.  This occurs because the
time at which the delay timer is set up occurs at some time between two clock
ticks.  Therefore, the first countdown tick occurs in less than the complete
time interval for a tick.  This can be a problem if the clock granularity is
large.

The rate monotonic scheduling algorithm is a hard real-time scheduling
methodology.  This methodology provides rules which allows one to guarantee
that a set of independent periodic tasks will always meet their deadlines even
under transient overload conditions.  The rate monotonic manager provides
directives built upon the Clock Manager's interval timer support routines.

Interval timing is not sufficient for the many applications which require that
time be kept in wall time or true calendar form.  Consequently, RTEMS maintains
the current date and time.  This allows selected time operations to be
scheduled at an actual calendar date and time.  For example, a task could
request to delay until midnight on New Year's Eve before lowering the ball at
Times Square.  The data type ``rtems_time_of_day`` is used to specify calendar
time in RTEMS services.  See :ref:`Time and Date Data Structures`.

.. index:: rtems_time_of_day

Obviously, the directives which use intervals or wall time cannot operate
without some external mechanism which provides a periodic clock tick.  This
clock tick is typically provided by a real time clock or counter/timer device.

Memory Management
=================
.. index:: memory management

RTEMS memory management facilities can be grouped into two classes: dynamic
memory allocation and address translation.  Dynamic memory allocation is
required by applications whose memory requirements vary through the
application's course of execution.  Address translation is needed by
applications which share memory with another CPU or an intelligent Input/Output
processor.  The following RTEMS managers provide facilities to manage memory:

- Region

- Partition

- Dual Ported Memory

RTEMS memory management features allow an application to create simple memory
pools of fixed size buffers and/or more complex memory pools of variable size
segments.  The partition manager provides directives to manage and maintain
pools of fixed size entities such as resource control blocks.  Alternatively,
the region manager provides a more general purpose memory allocation scheme
that supports variable size blocks of memory which are dynamically obtained and
freed by the application.  The dual-ported memory manager provides executive
support for address translation between internal and external dual-ported RAM
address space.