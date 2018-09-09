[![Build Status](https://travis-ci.com/nevrome/gluesless.svg?token=vxsQ9RjxoGASGtX4Q8jc&branch=master)](https://travis-ci.com/nevrome/gluesless)

## gluesless

gluesless is an idea expansion simulation. 

```
gluesless -pi <path_to_file> -ii <path_to_file> -o <path_to_file>

 Options:
  -pi --pajekfile		text file that describes network in .pajek format
  -ii --ideasfile		text file that describes idea as produced by popgenerator
  -o --outputfile 	output text file
  -q --quiet
```

## Installation

```
git clone git@github.com:snap-stanford/snap.git
cd snap	
make all
cd ..
git clone git@github.com:nevrome/gluesless.git
cd gluesless
make
```

## Citation

```
@Manual{clemens_schmid_gluesless_2018,
  address = {Kiel},
  title = {Gluesless: {{An}} Idea Expansion Simulation},
  author = {{Clemens Schmid}},
  year = {2018}
}
```
