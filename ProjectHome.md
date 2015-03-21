## Ngen Framework ##

The Ngen Framework is a powerful object-oriented cross-platform run-time that will be supplying native C++ with many features found in high-level managed languages like C# and Java.  The code base is completely written from scratch and takes advantage of the latest additions to the C++ standard (C11).  The goal of the project cannot be seen clearly yet, but the plan is to provide C++ developers with a rich framework for high-performance applications.

Languages like C# and Java would be useless without their accompanying frameworks due to the virtual layers between the code and the machine.  The NGEN framework will provide all the gems in huge frameworks like .NET and bring them down to the machine level where they can be useful in system development.

These features will be implemented via a series of components, and include, but are not limited to the following:

  * Unmanaged code reflection engine
  * Client-server networking
  * Diagnostics and testing
  * Scripting environment
  * Hardware access-layer
  * Content management system
  * Graphics and UI engine
  * Build system
  * Embedded platform build options
  * Database query engine

See the [Issues](http://code.google.com/p/ngen/issues/list) for the status of currently planned features.


---


## Sourcecode ##

The code is still in early stages of development, but a major version will be released by the end of this year. In the meantime you can check-out the latest stable version from the URL below:
```
svn checkout http://ngen.googlecode.com/svn/develop/v0.2 ngenframework/v0.2
```

**Warning:**  _Do not check-out from /svn/ or you will check-out all versions of the
source tree and other useless materials!_

For the latest development snapshot:
```
svn checkout http://ngen.googlecode.com/svn/develop/head ngenframework/head
```

Once checked-out, go [here](http://code.google.com/p/ngen/wiki/BuildingNgenFramework) for build instructions.


---


For a list of pre-built packages, see the table [here](http://code.google.com/p/ngen/wiki/PreBuiltPackages).
