# unitc

simple unit testing for C written using the m4 macro processor.

## How to use

Create an m4 file in ``/tests``.

In that start writing a test case as such:

```c
new_test(test_name){
  if(condition==1){
    return 0;
  }
  puts("Conditon was false");
  return 1;
} 
```
A test is a function that returns an integer and takes no parameters.

Tests must return 0 on success and return 1 on failure.

You may put as many tests in a single test file and as many test files in ``/tests`` as you please.

Run ``make`` and your tests will compile.

To run your tests run ``./run_tests``

## License

Unitc is open source software distributed under the BSD 3-Clause License.
