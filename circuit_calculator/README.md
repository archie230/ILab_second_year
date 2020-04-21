# CIrcuit calculator
Simple electrical circuit calculation program 

### Install:
```
git clone https://github.com/archie230/ILab_second_year.git
cd path/to/dir/ILab_second_year/circuit_calculator
make
```
### Run:
```
./bin/circalc filename.txt
```
### Input format:
circuit comes as list of vertices 

example: 
```
p1 -- p2, r; eV
Here p1, p2 are nodes, r is resistance, e is source emf (optional)
```

notes:

```
nodes must create range from 1 to n
n - number of nodes

it isn't possible to redefine edge like:

p1 -- p2, r;
then 
p2 -- p1, r;
```

### Output format:
list of currents between vertices
