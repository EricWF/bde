// bdlt_calendarreverseiterator.t.cpp                                 -*-C++-*-
#include <bdlt_calendarreverseiterator.h>

#include <bdls_testutil.h>

#include <bsl_cstdlib.h>
#include <bsl_sstream.h>

using namespace BloombergLP;
using namespace bsl;

// ============================================================================
//                             TEST PLAN
// ----------------------------------------------------------------------------
//                              Overview
//                              --------
// ----------------------------------------------------------------------------
// [11] CalendarReverseIterator();
// [ 2] CalendarReverseIterator(const iterator& value);
// [ 7] CalendarReverseIterator(const CalendarReverseIterator&);
// [ 2] ~CalendarReverseIterator();
// [ 9] CalendarReverseIterator& operator=(rhs);
// [14] CalendarReverseIterator& operator=(const iterator& rhs);
// [12] CalendarReverseIterator& operator++();
// [13] CalendarReverseIterator operator++(int);
// [12] CalendarReverseIterator& operator--();
// [13] CalendarReverseIterator operator--(int);
// [ 4] reference operator*() const;
// [ 4] pointer operator->() const;
// [ 4] iterator forwardIterator() const;
// [ 6] bool operator==(lhs, rhs);
// [ 6] bool operator!=(lhs, rhs);
// ----------------------------------------------------------------------------
// [ 1] BREATHING TEST
// [15] USAGE EXAMPLE
// [ 3] Reserved for 'gg' generator function.
// [ 5] Reserved for 'print' and 'operator<<' functions.
// [ 8] Reserved for 'swap' testing.
// [10] Reserved for BDEX streaming testing.
// ----------------------------------------------------------------------------

// ============================================================================
//                     STANDARD BDE ASSERT TEST FUNCTION
// ----------------------------------------------------------------------------

namespace {

int testStatus = 0;

void aSsErT(bool condition, const char *message, int line)
{
    if (condition) {
        cout << "Error " __FILE__ "(" << line << "): " << message
             << "    (failed)" << endl;

        if (0 <= testStatus && testStatus <= 100) {
            ++testStatus;
        }
    }
}

}  // close unnamed namespace

// ============================================================================
//               STANDARD BDE TEST DRIVER MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT       BDLS_TESTUTIL_ASSERT
#define ASSERTV      BDLS_TESTUTIL_ASSERTV

#define LOOP_ASSERT  BDLS_TESTUTIL_LOOP_ASSERT
#define LOOP0_ASSERT BDLS_TESTUTIL_LOOP0_ASSERT
#define LOOP1_ASSERT BDLS_TESTUTIL_LOOP1_ASSERT
#define LOOP2_ASSERT BDLS_TESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BDLS_TESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BDLS_TESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BDLS_TESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BDLS_TESTUTIL_LOOP6_ASSERT

#define Q            BDLS_TESTUTIL_Q   // Quote identifier literally.
#define P            BDLS_TESTUTIL_P   // Print identifier and value.
#define P_           BDLS_TESTUTIL_P_  // P(X) without '\n'.
#define T_           BDLS_TESTUTIL_T_  // Print a tab (w/o newline).
#define L_           BDLS_TESTUTIL_L_  // current Line number

// ============================================================================
//                                 USAGE EXAMPLE
// ----------------------------------------------------------------------------

// Note the following code is used by both the usage example and the rest of
// this test driver.

///Usage
///-----
// This section illustrates intended use of this component.
//
///Example 1: Basic Use of 'bdlt::CalendarReverseIterator'
/// - - - - - - - - - - - - - - - - - - - - - - - - - - -
// The following shows the intended usage of this component.
//
// First, we define a bidirectional iterator class:
//..
    template <class TYPE>
    class Iterator {
        // This 'class' basically behaves as a pointer to the parameterized
        // 'TYPE' with 5 'trait' types defines.  Note that it supports only a
        // subset of the functionality that a pointer would -- this subset
        // covers all the functionality that a 'bdlt_CalendarReverseIterator'
        // needs.
        //
        // The would have been implemented by inheriting from a pointer type
        // and adding the 5 typedefs, but C++ doesn't allow inheritance from
        // pointer types.

        TYPE *d_value;

        template <class OTHER>
        friend bool operator==(const Iterator<OTHER>&, const Iterator<OTHER>&);

      public:
        // PUBLIC TYPES
        typedef bsl::bidirectional_iterator_tag iterator_category;
        typedef TYPE                            value_type;
        typedef int                             difference_type;
        typedef TYPE *                          pointer;
        typedef TYPE&                           reference;

        // CREATORS
        Iterator() : d_value(0)
            // Construct a 'Iterator' object with the default value.
        {
        }

        Iterator(TYPE *value) : d_value(value)                      // IMPLICIT
            // Construct a 'Iterator' object from the specified 'value'.
        {
        }

        // Iterator(const Iterator&) = default;

        // ~Iterator() = default;

        // MANIPULATORS
        // Iterator& operator=(const Iterator&) = default;

        Iterator& operator++()
            // Increment this object and return a reference to it.
        {
            ++d_value;
            return *this;
        }

        Iterator& operator--()
            // Decrement this object and return a reference to it.
        {
            --d_value;
            return *this;
        }

        // ACCESSORS
        reference operator*() const
            // Return a reference to the item referred to by this object.
        {
            return *d_value;
        }

        pointer operator->() const
            // Return a pointer to the item referred to by this object.
        {
            return d_value;
        }

        Iterator operator+(bsl::ptrdiff_t offset) const
            // Return an iterator referencing the location at the specified
            // 'offset' from the element referenced by this iterator.
        {
            return Iterator(d_value + offset);
        }
    };

    template <class TYPE>
    inline
    bool operator==(const Iterator<TYPE>& lhs,  const Iterator<TYPE>& rhs)
        // Return 'true' if the specified 'lhs' is equivalent to the specified
        // 'rhs' and 'false' otherwise.
    {
        return lhs.d_value == rhs.d_value;
    }

    template <class TYPE>
    inline
    bool operator!=(const Iterator<TYPE>& lhs, const Iterator<TYPE>& rhs)
        // Return 'false' if the specified 'lhs' is equivalent to the specified
        // 'rhs' and 'true' otherwise.
    {
        return !(lhs == rhs);
    }
//..
// Then, we define 'struct' 'S', the type that will be pointed at by the
// 'Iterator' type:
//..
    struct S {
        char d_c;
        int  d_i;
    };
//..
// Next, we define 4 values for 'S':
//..
    const S s0 = { 'A', 3 };
    const S s1 = { 'B', 5 };
    const S s2 = { 'C', 7 };
    const S s3 = { 'D', 9 };
//..
// Then we define 's', a range of 'S' values:
//..
    S s[] = { s0, s1, s2, s3 };
    enum { NUM_S = sizeof s / sizeof *s };
//..
// Next, we define 'sfBegin', 'sfEnd'
//..
    Iterator<S> sfBegin(s + 0), sfEnd(s + NUM_S);
//..
// Then, we declare our reverse iterator type
//..
    typedef bdlt::CalendarReverseIterator<Iterator<S> > Reverse;
//..
// Next, we declare reverse begin and end iterators to our range of 'S's:
//..
    const Reverse rBegin(sfEnd), rEnd(sfBegin);
//..

// ============================================================================
//                     GLOBAL TYPEDEFS FOR TESTING
// ----------------------------------------------------------------------------

typedef bdlt::CalendarReverseIterator<Iterator<S> >      SObj;
typedef bdlt::CalendarReverseIterator<Iterator<double> > Obj;

// ============================================================================
//                             GLOBAL TEST DATA
// ----------------------------------------------------------------------------

S origS[] = { s0, s1, s2, s3 };

double v[] =     { 0.5, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
double origV[] = { 0.5, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
enum { NUM_V = sizeof v / sizeof *v };
Iterator<double> vfBegin(v + 0), vfEnd(v + NUM_V);

const double v0 = v[0];
const double v1 = v[1];
const double v2 = v[2];
const double v3 = v[3];
const double v4 = v[4];
const double v5 = v[5];
const double v6 = v[6];
const double v7 = v[7];
const double v8 = v[8];
const double v9 = v[9];

// ============================================================================
//                              MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    const int         test = argc > 1 ? atoi(argv[1]) : 0;
    const bool     verbose = argc > 2;
    const bool veryVerbose = argc > 3;

    cout << "TEST " << __FILE__ << " CASE " << test << endl;;

    switch (test) { case 0:
      case 15: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   Extracted from component header file.
        //
        // Concerns:
        //: 1 The usage example provided in the component header file compiles,
        //:   links, and runs as shown.
        //
        // Plan:
        //: 1 Incorporate usage example from header into test driver, remove
        //:   leading comment characters, and replace 'assert' with 'ASSERT'.
        //:   (C-1)
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "USAGE EXAMPLE" << endl
                          << "=============" << endl;

// Now, we traverse our range, streaming out the contents of the 'S' values:
//..
    bsl::ostringstream stream;
    for (Reverse it = rBegin; rEnd != it; ++it) {
        stream << (rBegin == it ? "" : ", ")
               << "{ "
               << it->d_c
               << ", "
               << it->d_i
               << " }";
    }
    stream << bsl::flush;
//..
// Finally, we verify the range output:
//..
    ASSERT(stream.str() == "{ D, 9 }, { C, 7 }, { B, 5 }, { A, 3 }");
//..

      } break;
      case 14: {
        // --------------------------------------------------------------------
        // ASSIGNMENT OPERATOR
        //   Ensure that we can assign the to any object of the class, such
        //   that the resultant object has the expected value.
        //
        // Concerns:
        //: 1 The assignment operator can change the value of any modifiable
        //:   target object to that of any source object.
        //:
        //: 2 The reference returned is to the target object (i.e., '*this').
        //:
        //: 3 The value of the source object is not modified.
        //
        // Plan:
        //: 1 For every possible iterator into the floating point and 'S'
        //:   arrays, use the value constructor to create an object 'X' having
        //:   the value from the iterator.  Assign to 'X' all possible
        //:   iterator values from the array, verify the resultant value of
        //:   'X', the return value of the assignment, and that the source
        //:   iterator is unmodified.  (C-1..3)
        //
        // Testing:
        //   CalendarReverseIterator& operator=(const iterator& rhs);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "ASSIGNMENT OPERATOR" << endl
                          << "===================" << endl;

        if (verbose) cout << "\nUse doubles." << endl;
        {
            for (int ti = 0; ti <= NUM_V; ++ti) {
                Obj mX(ti != NUM_V ? Obj(vfBegin + ti + 1) : Obj());

                const Obj& X(mX);

                for (int tj = 0; tj <= NUM_V; ++tj) {
                    const Iterator<double> iter = (tj != NUM_V
                                                   ? vfBegin + tj + 1
                                                   : Iterator<double>());

                    const Iterator<double> ITER(iter);

                    Obj *mR = &(mX = iter);

                    LOOP2_ASSERT(ti, tj, X.forwardIterator() == ITER);
                    LOOP2_ASSERT(ti, tj,                  mR == &mX);
                    LOOP2_ASSERT(ti, tj,                iter == ITER);
                }
            }
        }

        if (verbose) cout << "\nUse 'S's." << endl;
        {
            for (int ti = 0; ti <= NUM_S; ++ti) {
                SObj mX(ti != NUM_S ? SObj(sfBegin + ti + 1) : SObj());

                const SObj& X(mX);

                for (int tj = 0; tj <= NUM_V; ++tj) {
                    const Iterator<S> iter = (tj != NUM_S
                                              ? sfBegin + tj + 1
                                              : Iterator<S>());

                    const Iterator<S> ITER(iter);

                    SObj *mR = &(mX = iter);

                    LOOP2_ASSERT(ti, tj, X.forwardIterator() == ITER);
                    LOOP2_ASSERT(ti, tj,                  mR == &mX);
                    LOOP2_ASSERT(ti, tj,                iter == ITER);
                }
            }
        }
      } break;
      case 13: {
        // --------------------------------------------------------------------
        // POST-INCREMENT AND POST-DECREMENT
        //   Ensure that the post-increment and post-decrement operators work
        //   as expected.
        //
        // Concerns:
        //: 1 The operators correctly modify the state of the object.
        //:
        //: 2 The return value of the operators is as expected.
        //:
        //: 3 The returned iterator is modifiable and is associated with the
        //:   original array.
        //
        // Plan:
        //: 1 Using the floating point and 'S' arrays, for each element index
        //:   'ti' create two iterators 'X' and 'Z' where 'Z' is the expected
        //:   result of applying the operator to 'X'.  Apply the operator to
        //:   'X', verify the return value, verify the resultant value of 'X',
        //:   and verify modifying the returned iterator works as expected.
        //:   (C-1..3)
        //
        // Testing:
        //   CalendarReverseIterator operator++(int);
        //   CalendarReverseIterator operator--(int);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "POST-INCREMENT AND POST-DECREMENT" << endl
                          << "=================================" << endl;

        // Test with doubles.

        {
            double x = 3.2;

            for (int ti = 0; ti < NUM_V; ++ti, x *= 7.1) {
                Obj mX(vfBegin + ti + 1);  const Obj& X = mX;

                const Obj Z(vfBegin + ti);
                const Obj ZZ(X);

                Obj mY = mX++;  const Obj& Y = mY;

                LOOP_ASSERT(ti, X == Z);
                LOOP_ASSERT(ti, Y == ZZ);

                *mY = x;
                LOOP_ASSERT(ti, *ZZ == x);

                v[ti] = origV[ti];                 // restore to original state
            }

            for (int ti = 0; ti < NUM_V; ++ti, x *= 7.1) {
                Obj mX(vfBegin + ti);  const Obj& X = mX;

                const Obj Z(vfBegin + ti + 1);
                const Obj ZZ(X);

                Obj mY = mX--;  const Obj& Y = mY;

                LOOP_ASSERT(ti, X == Z);
                LOOP_ASSERT(ti, Y == ZZ);

                if (ti) {
                    *mY = x;
                    LOOP_ASSERT(ti, *ZZ == x);

                    v[ti - 1] = origV[ti - 1];     // restore to original state
                }
            }
        }

        // Test with 'S'.

        {
            int  i = 7;
            char c = 'f';

            for (int ti = 0;
                 ti < NUM_S;
                 ++ti, i *= 9, c = static_cast<char>('a' + i % 26)) {
                SObj mX(sfBegin + ti + 1);  const SObj& X = mX;

                const SObj Z(sfBegin + ti);
                const SObj ZZ(X);

                SObj mY = mX++;  const SObj& Y = mY;

                LOOP_ASSERT(ti, X == Z);
                LOOP_ASSERT(ti, Y == ZZ);

                mY->d_c = c;
                mY->d_i = i;

                LOOP_ASSERT(ti, ZZ->d_c == c);
                LOOP_ASSERT(ti, ZZ->d_i == i);

                s[ti] = origS[ti];                 // restore to original state
            }

            for (int ti = 0;
                 ti < NUM_S;
                 ++ti, i *= 9, c = static_cast<char>('a' + i % 26)) {
                SObj mX(sfBegin + ti);  const SObj& X = mX;

                const SObj Z(sfBegin + ti + 1);
                const SObj ZZ(X);

                SObj mY = mX--;  const SObj& Y = mY;

                LOOP_ASSERT(ti, X == Z);
                LOOP_ASSERT(ti, Y == ZZ);

                if (ti) {
                    mY->d_c = c;
                    mY->d_i = i;

                    LOOP_ASSERT(ti, ZZ->d_c == c);
                    LOOP_ASSERT(ti, ZZ->d_i == i);

                    s[ti - 1] = origS[ti - 1];     // restore to original state
                }
            }
        }
      } break;
      case 12: {
        // --------------------------------------------------------------------
        // PRE-INCREMENT AND PRE-DECREMENT
        //   Ensure that the pre-increment and pre-decrement operators work
        //   as expected.
        //
        // Concerns:
        //: 1 The operators correctly modify the state of the object.
        //:
        //: 2 The return value of the operators is as expected.
        //
        // Plan:
        //: 1 Using the floating point and 'S' arrays, for each element index
        //:   'ti' create two iterators 'X' and 'Z' where 'Z' is the expected
        //:   result of applying the operator to 'X'.  Apply the operator to
        //:   'X', verify the return value, and verify the resultant value of
        //:   'X'.  (C-1..2)
        //
        // Testing:
        //   CalendarReverseIterator& operator++();
        //   CalendarReverseIterator& operator--();
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "PRE-INCREMENT AND PRE-DECREMENT" << endl
                          << "===============================" << endl;

        // Test with doubles.

        {
            double x = 3.2;

            for (int ti = 0; ti < NUM_V; ++ti, x *= 7.1) {
                Obj mX(vfBegin + ti + 1);  const Obj& X = mX;

                const Obj Z(vfBegin + ti);

                Obj *mR = &(++mX);

                LOOP_ASSERT(ti,  X == Z);
                LOOP_ASSERT(ti, mR == &X);
            }

            for (int ti = 0; ti < NUM_V; ++ti, x *= 7.1) {
                Obj mX(vfBegin + ti);  const Obj& X = mX;

                const Obj Z(vfBegin + ti + 1);

                Obj *mR = &(--mX);

                LOOP_ASSERT(ti,  X == Z);
                LOOP_ASSERT(ti, mR == &X);
            }
        }

        // Test with 'S'.

        {
            for (int ti = 0; ti < NUM_S; ++ti) {
                SObj mX(sfBegin + ti + 1);  const SObj& X = mX;

                const SObj Z(sfBegin + ti);

                SObj *mR = &(++mX);

                LOOP_ASSERT(ti,  X == Z);
                LOOP_ASSERT(ti, mR == &X);
            }

            for (int ti = 0; ti < NUM_S; ++ti) {
                SObj mX(sfBegin + ti);  const SObj& X = mX;

                const SObj Z(sfBegin + ti + 1);

                SObj *mR = &(--mX);

                LOOP_ASSERT(ti,  X == Z);
                LOOP_ASSERT(ti, mR == &X);
            }
        }
      } break;
      case 11: {
        // --------------------------------------------------------------------
        // DEFAULT CTOR
        //   Ensure that we can use the default constructor to create an
        //   object (having the default-constructed value).
        //
        // Concerns:
        //: 1 An object created with the default constructor has the
        //:   contractually specified default value.
        //
        // Plan:
        //: 1 Create an object using the default constructor.  Verify, using
        //:   the 'forwardIterator' accessor, that the resulting object has
        //:   the expected value.  (C-1)
        //
        // Testing:
        //   CalendarReverseIterator();
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "DEFAULT CTOR" << endl
                          << "============" << endl;

        {
            Obj mX;  const Obj& X = mX;

            ASSERT(X.forwardIterator() == Iterator<double>());
        }
        {
            SObj mX;  const SObj& X = mX;

            ASSERT(X.forwardIterator() == Iterator<S>());
        }
      } break;
      case 10: {
        // --------------------------------------------------------------------
        // TESTING BDEX STREAMING
        //   There is no BDEX streaming for this component.
        //
        // Testing:
        //  Reserved for BDEX streaming testing.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING BDEX STREAMING" << endl
                          << "======================" << endl;

        if (verbose) cout << "Not implemented." << endl;
      } break;
      case 9: {
        // --------------------------------------------------------------------
        // COPY-ASSIGNMENT OPERATOR
        //   Ensure that we can assign the value of any object of the class to
        //   any object of the class, such that the two objects subsequently
        //   have the same value.
        //
        // Concerns:
        //: 1 The assignment operator can change the value of any modifiable
        //:   target object to that of any source object.
        //:
        //: 2 The signature and return type are standard.
        //:
        //: 3 The reference returned is to the target object (i.e., '*this').
        //:
        //: 4 The value of the source object is not modified.
        //:
        //: 5 Assigning an object to itself behaves as expected (alias-safety).
        //
        // Plan:
        //: 1 Use the address of 'operator=' to initialize a member-function
        //:   pointer having the appropriate signature and return type for the
        //:   copy-assignment operator defined in this component.  (C-2)
        //:
        //: 2 For every possible iterator into the floating point and 'S'
        //:   arrays, use the value constructor to create two 'const' objects,
        //:   'Z' and 'ZZ', both having the value from the iterator.  Create,
        //:   using all possible iterator values from the array, an object 'X'.
        //:   Assign to 'X' from 'Z' and verify the return value.  Use the
        //:   equality-comparison operator to verify that 'X' has the same
        //:   value as that of 'Z' and 'Z' still has the same value as that of
        //:   'ZZ'.  (C-1, 3..4)
        //:
        //: 3 For every possible iterator into the floating point and 'S'
        //:   arrays, use the value constructor to create one 'const' objects
        //:   'ZZ', having the value from the iterator.  Copy construct an
        //:   object 'X' from 'ZZ'.  Create a 'const' reference 'Y' to 'X'.
        //:   Assign to 'X' from 'Y' and verify the return value.  Use the
        //:   equality-comparison operator to verify that 'X' has the same
        //:   value as that of 'Y' and 'Y' still has the same value as that of
        //:   'ZZ'.  (C-5)
        //
        // Testing:
        //   CalendarReverseIterator& operator=(rhs);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "COPY-ASSIGNMENT OPERATOR" << endl
                          << "========================" << endl;

        if (verbose) cout <<
                 "\nAssign the address of the operator to a variable." << endl;
        {
            typedef Obj& (Obj::*operatorPtr)(const Obj&);

            // Verify that the signature and return type are standard.

            operatorPtr operatorAssignment = &Obj::operator=;

            (void)operatorAssignment;  // quash potential compiler warning
        }

        if (verbose) cout << "\nUse doubles." << endl;

        for (int ti = 0; ti <= NUM_V; ++ti) {
            const Obj Z(ti != NUM_V ? Obj(vfBegin + ti + 1) : Obj());
            const Obj ZZ(Z);

            for (int tj = 0; tj <= NUM_V; ++tj) {
                Obj        mX(tj != NUM_V ? Obj(vfBegin + tj + 1) : Obj());
                const Obj& X = mX;

                Obj *mR = &(mX = Z);

                LOOP2_ASSERT(ti, tj,  Z == X);
                LOOP2_ASSERT(ti, tj, mR == &mX);
                LOOP2_ASSERT(ti, tj, ZZ == Z);
            }

            {
                // self assignment

                Obj mX(Z);  const Obj& X = mX;

                const Obj& Y = mX;

                Obj *mR = &(mX = Y);

                LOOP_ASSERT(ti,  Y == X);
                LOOP_ASSERT(ti, mR == &mX);
                LOOP_ASSERT(ti, ZZ == Y);
            }
        }

        if (verbose) cout << "\nUse 'S's." << endl;

        for (int ti = 0; ti <= NUM_S; ++ti) {
            const SObj Z(ti != NUM_S ? SObj(sfBegin + ti + 1) : SObj());
            const SObj ZZ(Z);

            for (int tj = 0; tj <= NUM_S; ++tj) {
                SObj        mX(tj != NUM_S ? SObj(sfBegin + tj + 1) : SObj());
                const SObj& X = mX;

                SObj *mR = &(mX = Z);

                LOOP2_ASSERT(ti, tj,  Z == X);
                LOOP2_ASSERT(ti, tj, mR == &mX);
                LOOP2_ASSERT(ti, tj, ZZ == Z);
            }

            {
                // self assignment

                SObj mX(Z);  const SObj& X = mX;

                const SObj& Y = mX;

                SObj *mR = &(mX = Y);

                LOOP_ASSERT(ti,  Y == X);
                LOOP_ASSERT(ti, mR == &mX);
                LOOP_ASSERT(ti, ZZ == Y);
            }
        }
      } break;
      case 8: {
        // --------------------------------------------------------------------
        // SWAP MEMBER AND FREE FUNCTIONS
        //   There is no 'swap' methods implemented for this component.
        //
        // Testing:
        //  Reserved for 'swap' testing.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "SWAP MEMBER AND FREE FUNCTIONS" << endl
                          << "==============================" << endl;

        if (verbose) cout << "Not implemented." << endl;
      } break;
      case 7: {
        // --------------------------------------------------------------------
        // COPY CONSTRUCTOR
        //   Ensure that we can create a distinct object of the class from any
        //   other one, such that the two objects have the same value.
        //
        // Concerns:
        //: 1 The copy constructor creates an object having the same value as
        //:   that of the supplied original object.
        //:
        //: 2 The original object is passed as a reference providing
        //:   non-modifiable access to that object.
        //:
        //: 3 The value of the original object is unchanged.
        //
        // Plan:
        //: 1 For every possible iterator into the floating point and 'S'
        //:   arrays, use the value constructor to create two 'const' objects,
        //:   'Z' and 'ZZ', both having the value from the iterator.  Use the
        //:   copy constructor to create an object 'X' from 'Z'.  Use the
        //:   equality-comparison operator to verify that 'X' has the same
        //:   value as that of 'Z' and 'Z' still has the same value as that of
        //:   'ZZ'.  (C-1..3)
        //
        // Testing:
        //   CalendarReverseIterator(const CalendarReverseIterator&);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "COPY CONSTRUCTOR" << endl
                          << "================" << endl;

        // Test the default constructed objects.

        {
            const Obj Z;
            const Obj ZZ;

            const Obj X(Z);

            // Verify the value of the object.

            ASSERT(Z == X);

            // Verify that the value of 'Z' has not changed.

            ASSERT(ZZ == Z);
        }

        {
            const SObj Z;
            const SObj ZZ;

            const SObj X(Z);

            // Verify the value of the object.

            ASSERT(Z == X);

            // Verify that the value of 'Z' has not changed.

            ASSERT(ZZ == Z);
        }

        // Test with doubles.

        for (int ti = 0; ti < NUM_V; ++ti) {
            const Obj Z( vfBegin + ti + 1);
            const Obj ZZ(vfBegin + ti + 1);

            const Obj X(Z);

            // Verify the value of the object.

            LOOP_ASSERT(ti, Z == X);

            // Verify that the value of 'Z' has not changed.

            LOOP_ASSERT(ti, ZZ == Z);
        }

        // Test with 'S's.

        for (int ti = 0; ti < NUM_S; ++ti) {
            const SObj Z( sfBegin + ti + 1);
            const SObj ZZ(sfBegin + ti + 1);

            const SObj X(Z);

            // Verify the value of the object.

            LOOP_ASSERT(ti, Z == X);

            // Verify that the value of 'Z' has not changed.

            LOOP_ASSERT(ti, ZZ == Z);
        }

      } break;
      case 6: {
        // --------------------------------------------------------------------
        // EQUALITY-COMPARISON OPERATORS
        //   Ensure that '==' and '!=' are the operational definition of value.
        //
        // Concerns:
        //: 1 Two objects, 'X' and 'Y', compare equal if and only if their
        //:   corresponding year/month/day representations compare equal.
        //:
        //: 2 'true  == (X == X)' (i.e., identity).
        //:
        //: 3 'false == (X != X)' (i.e., identity).
        //:
        //: 4 'X == Y' if and only if 'Y == X' (i.e., commutativity).
        //:
        //: 5 'X != Y' if and only if 'Y != X' (i.e., commutativity).
        //:
        //: 6 'X != Y' if and only if '!(X == Y)'.
        //:
        //: 7 Comparison is symmetric with respect to user-defined conversion
        //:   (i.e., both comparison operators are free functions).
        //:
        //: 8 Non-modifiable objects can be compared (i.e., objects or
        //:   references providing only non-modifiable access).
        //:
        //: 9 The equality-comparison operators' signatures and return types
        //:   are standard.
        //
        // Plan:
        //: 1 Use the respective addresses of 'operator==' and 'operator!=' to
        //:   initialize function pointers having the appropriate signatures
        //:   and return types for the two homogeneous, free equality-
        //:   comparison operators defined in this component.  (C-7..9)
        //:
        //: 2 Using the floating point and 'S' arrays, for each element index
        //:   'ti' and 'tj' create reverse iterators from forward iterators
        //:   accessing the indexed elements and verify the results of the
        //:   operators using the comparason of the indices as an oracle for
        //:   the results.  (C-1..6)
        //
        // Testing:
        //   bool operator==(lhs, rhs);
        //   bool operator!=(lhs, rhs);
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "EQUALITY-COMPARISON OPERATORS" << endl
                          << "=============================" << endl;

        if (verbose) cout <<
                "\nAssign the address of each operator to a variable." << endl;
        {
            typedef bool (*operatorPtr)(const Obj&, const Obj&);

            // Verify that the signatures and return types are standard.

            operatorPtr operatorEq = bdlt::operator==;
            operatorPtr operatorNe = bdlt::operator!=;

            (void)operatorEq;  // quash potential compiler warnings
            (void)operatorNe;
        }

        if (verbose) cout << "\nTest with doubles." << endl;

        for (int ti = 0; ti < NUM_V; ++ti) {
            Obj lhs(vfBegin + ti + 1);

            for (int tj = 0; tj < NUM_V; ++tj) {
                Obj rhs(vfBegin + tj + 1);

                LOOP2_ASSERT(ti, tj, (ti == tj) == (lhs == rhs));
                LOOP2_ASSERT(ti, tj, (ti != tj) == (lhs != rhs));
            }
        }

        if (verbose) cout << "\nTest with 'S's." << endl;

        for (int ti = 0; ti < NUM_V; ++ti) {
            SObj lhs(sfBegin + ti + 1);

            for (int tj = 0; tj < NUM_V; ++tj) {
                SObj rhs(sfBegin + tj + 1);

                LOOP2_ASSERT(ti, tj, (ti == tj) == (lhs == rhs));
                LOOP2_ASSERT(ti, tj, (ti != tj) == (lhs != rhs));
            }
        }
      } break;
      case 5: {
        // --------------------------------------------------------------------
        // PRINT AND OUTPUT OPERATOR (<<)
        //   There are no 'print' and 'operator<<' for this component.
        //
        // Testing:
        //   Reserved for 'print' and 'operator<<' functions.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "PRINT AND OUTPUT OPERATOR (<<)" << endl
                          << "==============================" << endl;

        if (verbose) cout << "No 'print' and 'operator<<' functions." << endl;

      } break;
      case 4: {
        // --------------------------------------------------------------------
        // BASIC ACCESSORS
        //   Ensure each basic accessor properly interprets object state.
        //
        // Concerns:
        //: 1 Each of the basic accessors returns the expected value.
        //:
        //: 2 Each basic accessor method is declared 'const'.
        //
        // Plan:
        //: 1 Traverse the range of doubles with a reverse iterator.
        //:   1 Compare the result of 'operator*' with the expected value
        //:     arrived at through array access.
        //:   2 Assign a new value to the reference returned by 'operator*',
        //:     verifying it is a reference to a modifying, and verify through
        //:     array access that the right memory location was modified.
        //:
        //: 2 Traverse the range of 'S's with a reverse iterator.
        //:   1 Compare the result of 'operator->' with the expected value
        //:     arrived at through array access.
        //:   2 Assign a new value to the reference returned by 'operator->',
        //:     verifying it is a reference to a modifying, and verify through
        //:     array access that the right memory location was modified.
        //:
        //: 3 Traverse the doubles with a reverse iterator and a forward
        //:   iterator at the same time.
        //:   1 Apply the 'forwardIterator' accessor to the reverse iterator
        //:     and verify the result is equal to the forward iterator.
        //
        // Testing:
        //   reference operator*() const;
        //   pointer operator->() const;
        //   iterator forwardIterator() const;
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "BASIC ACCESSORS" << endl
                          << "===============" << endl;

        if (verbose) cout << "Traverse the doubles verifying 'operator*'.\n";
        {
            double x = 3.2;

            for (int ti = 0; ti < NUM_V; ++ti, x *= 7.1) {
                Obj it(vfBegin + ti + 1);

                if (veryVerbose) { P_(v[ti]) P(*it); }

                LOOP_ASSERT(ti, v[ti] == *it);
                *it = x;
                LOOP_ASSERT(ti, v[ti] == x);

                v[ti] = origV[ti];                 // restore to original state
            }
        }

        if (verbose) cout << "Traverse the 'S's verifying 'operator->'.\n";
        {
            int  i = 7;
            char c = 'f';

            for (int ti = 0;
                 ti < NUM_S;
                 ++ti, i *= 9, c = static_cast<char>('a' + i % 26)) {
                SObj it(sfBegin + ti + 1);

                if (veryVerbose) { P_(it->d_c) P(it->d_i); }

                LOOP_ASSERT(ti, s[ti].d_c == it->d_c);
                LOOP_ASSERT(ti, s[ti].d_i == it->d_i);

                it->d_c = c;
                it->d_i = i;

                LOOP_ASSERT(ti, s[ti].d_c == c);
                LOOP_ASSERT(ti, s[ti].d_i == i);

                s[ti] = origS[ti];                 // restore to original state
            }
        }

        if (verbose) {
            cout << "Traverse the doubles verifying 'forwardIterator'.\n";
        }
        {
            Iterator<double> f = vfBegin + 1;

            for (int ti = 0; ti < NUM_V; ++ti, ++f) {
                Obj it(vfBegin + ti + 1);

                LOOP_ASSERT(ti, f == it.forwardIterator());
            }
        }
      } break;
      case 3: {
        // --------------------------------------------------------------------
        // GENERATOR FUNCTION 'gg'
        //   There is no 'gg' function for this component.
        //
        // Testing:
        //   Reserved for 'gg' generator function.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "GENERATOR FUNCTION 'gg'" << endl
                          << "=======================" << endl;

        if (verbose) cout << "No 'gg' function for 'bdlt::Date'." << endl;

      } break;
      case 2: {
        // --------------------------------------------------------------------
        // VALUE CTOR & DTOR
        //   Ensure that we can use the value constructor to create an object
        //   having any state relevant for thorough testing, and use the
        //   destructor to destroy it safely.
        //
        // Concerns:
        //: 1 The value constructor can create an object to have any value that
        //:   does not violate the method's documented preconditions.
        //:
        //: 2 An object can be safely destroyed.
        //
        // Plan:
        //: 1 Directly test the value constructor.  (C-1)
        //:
        //: 2 Let the object created in P-1 go out of scope.  (C-2)
        //
        // Testing:
        //   CalendarReverseIterator(const iterator& value);
        //   ~CalendarReverseIterator();
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "VALUE CTOR & DTOR" << endl
                          << "=================" << endl;

        for (int i = 0; i < NUM_V; ++i) {
            Obj mX(vfBegin + i + 1);  const Obj& X = mX;

            LOOP_ASSERT(i, *X == *(vfBegin + i));
        }

        for (int i = 0; i < NUM_S; ++i) {
            SObj mX(sfBegin + i + 1);  const SObj& X = mX;

            LOOP_ASSERT(i, (*X).d_c == (*(sfBegin + i)).d_c);
            LOOP_ASSERT(i, (*X).d_i == (*(sfBegin + i)).d_i);
        }
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //
        // Concerns:
        //: 1 The class is sufficiently functional to enable comprehensive
        //:   testing in subsequent test cases.
        //
        // Plan:
        //: 1 Start with an array of 'double's, and create 'Iterator' iterators
        //:   pointing to the begin ('vfBegin') and end ('vfEnd') of that
        //:   array.
        //:
        //: 2 Create reverse begin and end iterators from the forward
        //:   iterators.
        //:
        //: 3 Create other reverse iterator objects by copying from the
        //:   begin and end reverse iterators, and manipulate with with pre
        //:   and post increments and decrements, verifying that, when
        //:   dereferenced, they show that they are pointing to the right
        //:   'double' values.
        //:
        //: 4 Traverse the length of the range.
        //:
        //: 5 Verify that a reference to a modifiable is returned by modifying
        //:   the 'doubles' returned to, across the range.
        //:
        //: 6 Traverse the range again, verifying that the 'double' values are
        //:   as expected.
        //
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "BREATHING TEST" << endl
                          << "==============" << endl;

        if (verbose) cout << "Initialize reverse 'begin' and 'end' from\n"
                             "'Iterator' type iterators\n";

        const Obj vrBegin(vfEnd), vrEnd(vfBegin);
        ASSERT(vrBegin != vrEnd);

        if (verbose) cout << "Test default c'tor\n";
        {
            Obj it;
            it = vrBegin;
            ASSERT(vrBegin == it);
            ASSERT(vrEnd   != it);
        }

        if (verbose) cout << "Test copy c'tor\n";

        Obj it = vrBegin;
        ASSERT(vrBegin == it);
        ASSERT(vrEnd   != it);

        if (verbose) cout << "Test 'operator*'\n";
        {
            ASSERT(v9 == *it);
        }

        if (verbose) cout << "Test 'operator++' and its return value.\n";
        {
            ASSERT(v8 == *++it);
            ASSERT(v8 == *it);
            ASSERT(vrBegin != it);
        }

        if (verbose) cout << "Test post decrement.\n";

        Obj jit = it--;
        ASSERT(v8 == *jit);
        ASSERT(v9 == *it);
        ASSERT(vrBegin == it);
        ASSERT(it != jit);

        if (verbose) cout << "Test post increment.\n";
        {
            ASSERT(v9 == *it++);
            ASSERT(v8 == *it);
        }

        if (verbose) cout << "Test pre decrement.\n";
        {
            ASSERT(v9 == *--it);
            ASSERT(vrBegin == it);
            ASSERT(vrEnd != it);
        }

        if (verbose) cout << "Pre increment through the sequence.\n";
        {
            ASSERT(vrBegin == it++);
            ASSERT(v8 == *it);
            ASSERT(v7 == *++it);
            ASSERT(v6 == *++it);
            ASSERT(v5 == *++it);
            ASSERT(v4 == *++it);
            ASSERT(v3 == *++it);
            ASSERT(v2 == *++it);
            ASSERT(v1 == *++it);
            ASSERT(v0 == *++it);
            ASSERT(vrEnd != it);
            ASSERT(vrEnd == ++it);
            ASSERT(vrEnd == it);
        }

        if (verbose) cout << "Decrement back a bit from the end.\n";
        {
            ASSERT(v0 == *--it);
            ASSERT(v1 == *--it);
            ASSERT(v1 == *it--);
        }

        if (verbose) cout << "Iterate through the whole sequence.\n";
        {
            int ti = NUM_V - 1;
            for (it = vrBegin; vrEnd != it; ++it, --ti) {
                if (veryVerbose) { P_(v[ti]) P(*it); }

                LOOP3_ASSERT(v[ti], ti, *it, v[ti] == *it);
            }
            ASSERT(-1 == ti);
        }
      } break;
      default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = " << testStatus << "." << endl;
    }
    return testStatus;
}
// ----------------------------------------------------------------------------
// Copyright 2015 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
