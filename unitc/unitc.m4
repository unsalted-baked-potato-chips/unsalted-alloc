/*
BSD 3-Clause License

Copyright (c) 2022, Robert Herlihy
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

divert(0)

define(`new_test', `divert(1) $1, divert(2) "$1", divert(0) int $1()')

define(`include_all',
    `ifelse(
        $1, `', , `1', `1', `changecom(`{',`}') include($1) changecom() include_all(shift($@))'
    )'
)
include_all(test_includes)


static const int (*_unitc_unit_tests[])(void)= {
    undivert(1)
    NULL
};

static const char * _unitc_test_names[] = {
    undivert(2)
};

#include <stdio.h>
int main(){
    unsigned int failed_tests = 0;
    for (size_t i=0; _unitc_unit_tests[i]!=NULL; i++){
        int result = !!(_unitc_unit_tests[i]());
        printf("%s: %s.\n",_unitc_test_names[i], result?"FAILED":"PASSED");
        failed_tests += result;
    }
    if (failed_tests){
        printf("FAILED %u TESTS.\n", failed_tests);
    }else{
        puts("ALL TESTS PASSED");   
    }
    return failed_tests;
}
