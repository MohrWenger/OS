#include <stdio.h>
#include "uthreads.h"
#include <iostream>

using namespace std;
static int counter = 0;

void f()
{
    for (;;)
    {
        ++counter;
        if (counter % 100000000 == 0)
        {
            cout << "I'm thread 1 and my quantums are: "
                 << uthread_get_quantums(uthread_get_tid()) << endl;
            if (uthread_get_quantums(1) == 3)
            {
                cout << "XXXXXX  Thread 1 is terminated  XXXXXX" << endl;
                uthread_terminate(1);
            }
        }
    }
}


void g()
{
    for (;;)
    {
        ++counter;
        if (counter % 100000000 == 0)
        {
            cout << "I'm thread 2 and my quantums are: "
                 << uthread_get_quantums(2) << endl;
            if (uthread_get_quantums(2) == 5)
            {
                cout << "ZZZZZ Thread 2 is going to Sleep  ZZZZZ" << endl;
                uthread_sleep(1000000000);
            }
        }
    }
}


void h()
{
    for (;;)
    {
        ++counter;
        if (counter % 100000000 == 0)
        {
            cout << "I'm thread 3 and my quantums are: " << uthread_get_quantums(3) << endl;
//            if (uthread_get_quantums(3) == 5)
//            {
//                cout << "BBBBB Thread 3 blocked Thread 2   BBBBB" << endl;
//                uthread_block(2);
//            }
            if (uthread_get_quantums(3) == 5)
            {
                cout << "XXXXXX  Thread 2 is terminated by thread 3  XXXXXX" << endl;
                cout << uthread_terminate(2) << endl;
            }
        }
    }
}


void i()
{
    for (;;)
    {
        ++counter;
        if (counter % 100000000 == 0)
        {
            cout << "I'm thread 4 and my quantums are: "
                 << uthread_get_quantums(uthread_get_tid()) << endl;
            if (uthread_get_quantums(4) == 7)
            {
                cout << "TTTTT Thread 4 bringing sexy back Thread 2 RRRRR" << endl;
                uthread_resume(2);
            }
            if (uthread_get_quantums(4) == 10)
            {
                cout << "TTTTT Thread 4 terminates Thread 0 TTTTT" << endl;
                cout << uthread_terminate(0) << endl;
            }
//            if (uthread_get_quantums(4) == 7)
//            {
//                cout << "XXXXXX  Thread 2 is terminated by thread 4    XXXXXX" << endl;
//                cout << uthread_terminate(2) << endl;
//            }
        }
    }
}


int main()
{
    cout << "Init from main: " << boolalpha << bool(uthread_init(300000) == 0) << endl;
    cout << uthread_spawn(&f) << endl;
    cout << uthread_spawn(&g) << endl;
    cout << uthread_spawn(&h) << endl;
    cout << uthread_spawn(&i) << endl;
    for (;;)
    {
        ++counter;
        if (counter % 100000000 == 0)
        {
            cout << "I'm the main!" << " and my quantums are: "
                 << uthread_get_quantums(0) << endl;
        }
    }
}

/**

             if (uthread_get_quantums(2) == 3)
            {
                cout << "Sleeeeeeeeeep" << endl;
                uthread_sleep(1000000000);
            }


            cout << uthread_block(2) << " is blocked." << endl;

*/