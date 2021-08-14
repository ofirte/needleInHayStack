# needleInHayStack

needleInHayStack is a cpp script for searching patterns in large text files.

## Installation

Download the .cpp file and compile it using g++ or any other C++ compilar.


```bash
g++ -o find .\find.cpp
```

## Usage

```bash
./find <pattern> <file_path>
```
For your convenience run the python script the generate a test file of 2GB.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## remarks
The script doesn't load the entire file into memory, it loads only 2mb on ram.

Fastest line counting method was with memchar.

Running the search with two threads slightly improved the performance results.

For even faster processing, I used two threads to for each buffer load from the file.

Which imporve performace on my machine by 10%.
