Diploma project
======
Advanced Graph Analyzer
(master diploma project repository)
## User Manual


### 1. Installation
#####	Steps for configuration of development environment:
-	GCC version must be 4.6 or above (if it is possible install 4.8)
-	 Download sources, extract somewhere (let's assume folder name is extracted_dir) http://www.mpich.org/static/downloads/3.0.4/mpich-3.0.4.tar.gz
-	Change current directory to extracted_dir
-	`./configure --enable-shared --enable-sharedlibs=gcc`
-	`make && sudo make install` (this will install mpich3 to /usr/local/lib, /usr/local/bin etc.), note: All versions of mpi must be uninstalled before installation with this instruction. 
-	 Download boost source (do not install with apt-get, it is needed to compile it using mpi settings) http://sourceforge.net/projects/boost/files/boost/1.53.0/. Then set BOOST_LIBS environment variable to point on boost installation directory.
-	 Read http://www.boost.org/doc/libs/1_53_0/doc/html/mpi/getting_started.html#mpi.config
-	When building boost, edit user-config.jam file and add following line:  `using mpi : /usr/local/bin/mpic++ ; `(don't miss up white spaces around ':' and ';').
-	Make sure that all previous versions of mpich3 are uninstalled.
-	Proceed to building and installing of boost.

##### Steps for external libs installation:
-	From central place, `cd install/compile` directory and run `load_external_libs.sh` script.
This will automatically configure OGDF and libxl packages.
-	The installation also requires following packages to be installed: Eigen (https://eigen.tuxfamily.org/dox/GettingStarted.html), igraph (http://igraph.org/c/).

### 2. Building system
-	From central place, cd subsystem for which you want to (re)-generate executable and run make or make debug, for release and debug builds correspondingly. The location of generated executable is $(pwd)/lib/ directory.

### 3. Testing system (Unit tests)
    ./unit_tests/run_tests.sh – For running all existing unit_tests

### 4. Practical Usage
#####	Graph Generation
    graph_generator.exe –M [random_graph_model] -N [number_of_vertices] -p [probability] –E [number_of_edges] –f [output_file] –t [storage_core_type]
 
 *Note: number_of_edges and probability are mutually exclusive properties 1st should be specified only in case of Block-Hierarchical model and 2nd for Erdos-Reyni model.*

##### Alternate Property Computer and Community Detection
    ./scripts/apc_runner.sh [configuration file]
###### Configuration input file prototype

    <?xml version="1.0"?>
    <config>
    <graphs>
        <graph-path></graph-path>
    </graphs>
    <community-graph></community-graph>
    <properties>
        <property></property>
        <property></property>
        <property></property>
        <property></property>
    </properties>
    <calculate-distribution></calculate-distribution>
    <calcuate-average></calcuate-average>
    <max-parallel-proc-count></max-parallel-proc-count>
    </config>

##### Property Average Calculation

    ./scripts/avg_calc.sh
    
*Calculates and stores averages of properties given in config.xml under avg_results folder.
To enable this feature user must set calcuate-average option in configuration file as true(or 1)*
##### Graph Converter
    graph_converter.exe [flag] [first_file_name] [second_file_name] 

 *Note: [flag] is 'b', then [first_file_name] must be boost graph file name, [second_file_name] must be standard graph file name.If [flag] is 's', then [first_file_name] must be standard graph file name, [second_file_name] must be boost graph file name.*

### 5. Developers Guide
####### A couple of additional things to be done after the installation step
- Install if needed the gtest unit-tests library (https://github.com/google/googletest).
