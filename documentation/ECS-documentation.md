<h1 align="center"> Engine documentation </h1>

<br>

<p align="center">
  <a href="#what-is-ecs?">What is ECS</a> &#xa0; | &#xa0;
  <a href="#caracteristics">Caracteristics</a> &#xa0; | &#xa0;
  <a href="#variants">Variants</a> &#xa0; | &#xa0;
  <a href="#what-is-a-client-?">Wat is a Client ?</a> &#xa0; | &#xa0;
  <a href="#what is a server?">What is a Server ?</a> &#xa0; | &#xa0;
  <a href="#sources">Sources</a>
</p>

<br>

## What is ECS ##

ECS stands for Entity Component System. It is a software architecture model mainly used in video game development for the representation of objects in the game world. An ECS consists of entities composed of data components, with systems that operate on the components of the entities.
ECS follows the principle of composition rather than inheritance, which means that each entity is defined not by a hierarchy of types, but by its associated components. The systems act globally on all entities that have the required components.

### Characteristics ###
   `Entity`: An entity represents a general purpose object. In a game engine context, for example, each rough game object is represented as an entity. Usually it is just a unique identifier. Implementations usually use a simple integer for this.

   `Component`: a component labels an entity as having a particular aspect and contains the data necessary to model that aspect. For example, each game object that is susceptible to damage may have a Health component associated with its entity. Implementations usually use
   structures, classes or associative arrays.

   `System`: A system is a process that acts on all entities with the desired components. For example, a physical system can search for entities with mass, velocity and position components, and iterate on the results by performing physical calculations on the sets of components for each entity.

   The behavior of an entity can be modified at runtime by systems that add, remove, or modify components. This eliminates the ambiguity problems of deep and broad inheritance hierarchies often found in object-oriented programming techniques that are difficult to understand, maintain
   and extend. Common ECS approaches are highly compatible with and often associated with data-driven design techniques. Data from all instances of a component are typically stored together in physical memory, allowing efficient memory access for systems that
   systems that operate on many entities.

 ### Variants ###
   The data layout of the different ECSs may differ, as well as the definition of the components, their relationship with the entities and the way in which the systems access the components of the entities.
    An entity consists only of an ID to access components. It is common to use a unique ID for each entity. This is not a requirement, but it has several advantages:

- The entity can be referenced using the ID instead of a pointer. This is more robust, as it would allow the entity to be destroyed without leaving dangling pointers.
- This helps to store the state externally. When the state is loaded again, there is no need to rebuild the pointers.
- Data can be shuffled in memory as needed.
- Entity identifiers can be used when communicating over a network to uniquely identify the entity. Some of these benefits can also be achieved using smart pointers.

The Unity game engine <br>
    The Unity layout has tables each with columns of components. In this system, an entity type is based on the components it contains. For each entity type, there is a table (called archetype) containing component columns that correspond to the components used in the entity. To access to a particular entity, one must find the correct archetype (table) and index into each column to obtain each component corresponding to that entity.

Apparatus <br>
    Apparatus is a third-party ECS implementation for Unreal Engine that has introduced additional features to the common ECS paradigm. One of these features is the support of type hierarchy for components. Each component can have a base component type (or base class) much like in OOP. A system can then query the base class and match all its descendants in the resulting entity selection. This can be very useful to have a common logic implemented on a set of different components and adds an extra dimension to the paradigm.

### What is a Client ? ###
A client is a computer or a program that, as part of its operation, relies on sending a request to another program or a computer hardware or software that accesses a service made available by a server (which may or may not be located on another computer).For example, web browsers are clients that connect to web servers and retrieve web pages for display. Email clients retrieve email from mail servers. Online chat uses a variety of clients, which vary on the chat protocol being used. Multiplayer video games or online video games may run as a client on each computer. The term "client" may also be applied to computers or devices that run the client software or users that use the client software.

A client is part of a client–server model, which is still used today. Clients and servers may be computer programs run on the same machine and connect via inter-process communication techniques. Combined with Internet sockets, programs may connect to a service operating on a possibly remote system through the Internet protocol suite. Servers wait for potential clients to initiate connections that they may accept.

### What is a Server ? ###

In computing, a server is a piece of computer hardware or software (computer program) that provides functionality for other programs or devices, called "clients". This architecture is called the client–server model. Servers can provide various functionalities, often called "services", such as sharing data or resources among multiple clients, or performing computation for a client. A single server can serve multiple clients, and a single client can use multiple servers. A client process may run on the same device or may connect over a network to a server on a different device.[1] Typical servers are database servers, file servers, mail servers, print servers, web servers, game servers, and application servers.[2]

Client–server systems are usually most frequently implemented by (and often identified with) the request–response model: a client sends a request to the server, which performs some action and sends a response back to the client, typically with a result or acknowledgment. Designating a computer as "server-class hardware" implies that it is specialized for running servers on it. This often implies that it is more powerful and reliable than standard personal computers, but alternatively, large computing clusters may be composed of many relatively simple, replaceable server components.


## Sources ##
https://en.wikipedia.org/wiki/Entity_component_system<br>
https://en.wikipedia.org/wiki/Client_(computing)<br>
https://en.wikipedia.org/wiki/Server_(computing)<br>