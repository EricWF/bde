// bdlb_cstringhash.t.cpp                                             -*-C++-*-

#include <bdlb_cstringhash.h>

#include <bslalg_hashutil.h>
#include <bslalg_hastrait.h>
#include <bslalg_typetraits.h>

#include <bslma_default.h>
#include <bslma_defaultallocatorguard.h>
#include <bslma_testallocator.h>
#include <bslma_testallocatormonitor.h>

#include <bslmf_issame.h>

#include <bsls_assert.h>
#include <bsls_asserttest.h>

#include <bsl_iostream.h>

#include <bsl_cstdlib.h>
#include <bsl_cstring.h>

using namespace BloombergLP;
using namespace bsl;

//=============================================================================
//                             TEST PLAN
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// [ 3] operator()(const char *, const char *) const
// [ 2] CStringHash()
// [ 2] CStringHash(const CStringHash)
// [ 2] ~CStringHash()
// [ 2] CStringHash& operator=(const CStringHash&)
// ----------------------------------------------------------------------------
// [ 1] BREATHING TEST
// [ 7] USAGE EXAMPLE
// [ 4] Standard typedefs
// [ 5] Bitwise-movable trait
// [ 5] IsPod trait
// [ 6] QoI: Is an empty type

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
//               STANDARD BSL TEST DRIVER MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT       BSLS_BSLTESTUTIL_ASSERT
#define ASSERTV      BSLS_BSLTESTUTIL_ASSERTV

#define LOOP_ASSERT  BSLS_BSLTESTUTIL_LOOP_ASSERT
#define LOOP0_ASSERT BSLS_BSLTESTUTIL_LOOP0_ASSERT
#define LOOP1_ASSERT BSLS_BSLTESTUTIL_LOOP1_ASSERT
#define LOOP2_ASSERT BSLS_BSLTESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLS_BSLTESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLS_BSLTESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLS_BSLTESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLS_BSLTESTUTIL_LOOP6_ASSERT

#define Q            BSLS_BSLTESTUTIL_Q   // Quote identifier literally.
#define P            BSLS_BSLTESTUTIL_P   // Print identifier and value.
#define P_           BSLS_BSLTESTUTIL_P_  // P(X) without '\n'.
#define T_           BSLS_BSLTESTUTIL_T_  // Print a tab (w/o newline).
#define L_           BSLS_BSLTESTUTIL_L_  // current Line number

// ============================================================================
//                  NEGATIVE-TEST MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT_SAFE_PASS(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_PASS(EXPR)
#define ASSERT_SAFE_FAIL(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_FAIL(EXPR)
#define ASSERT_PASS(EXPR)      BSLS_ASSERTTEST_ASSERT_PASS(EXPR)
#define ASSERT_FAIL(EXPR)      BSLS_ASSERTTEST_ASSERT_FAIL(EXPR)
#define ASSERT_OPT_PASS(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_PASS(EXPR)
#define ASSERT_OPT_FAIL(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_FAIL(EXPR)

//=============================================================================
//                    GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------
typedef bdlb::CStringHash Obj;

// ============================================================================
//                                 TYPE TRAITS
// ----------------------------------------------------------------------------

BSLMF_ASSERT(bsl::is_trivially_copyable<Obj>::value);
BSLMF_ASSERT(bsl::is_trivially_default_constructible<Obj>::value);

//=============================================================================
//                             USAGE EXAMPLE
//-----------------------------------------------------------------------------

// ============================================================================
//                            MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int                 test = argc > 1 ? atoi(argv[1]) : 0;
    bool             verbose = argc > 2;
    bool         veryVerbose = argc > 3;
    bool     veryVeryVerbose = argc > 4;
    bool veryVeryVeryVerbose = argc > 5;

    cout << "TEST " << __FILE__ << " CASE " << test << endl;

    // CONCERN: In no case does memory come from the global allocator.

    bslma::TestAllocator globalAllocator("global", veryVeryVeryVerbose);
    bslma::Default::setGlobalAllocator(&globalAllocator);

    switch (test) { case 0:
      case 7: {
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

      } break;
      case 6: {
        // --------------------------------------------------------------------
        // QoI: Is an empty type
        //   As a quality of implementation issue, the class has no state and
        //   should support the use of the empty base class optimization on
        //   compilers that support it.
        //
        // Concerns:
        //: 1 class 'bdlb::CStringHash' does not increase the size of an object
        //:   when used as a base class.
        //
        // Plan:
        //: 1 Define a non-empty class with no padding, 'TwoInts'.
        //:
        //: 2 Assert that 'TwoInts has the expected size of 8 bytes.
        //:
        //: 3 Create a class, 'DerivedInts', with identical structure to
        //:   'TwoInts' but derived from 'bdlb::CStringHash'.
        //:
        //: 4 Assert that both classes have the same size.
        //:
        //: 5 Create a class, 'IntsWithMember', with identical structure to
        //:   'TwoInts' and an 'bdlb::CStringHash' additional data member.
        //:
        //: 6 Assert that 'IntsWithMember' is larger than the other two
        //:   classes.
        //
        // Testing:
        //   QoI: Support for empty base optiization
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING QoI: Is an empty type" << endl
                          << "=============================" << endl;

        struct TwoInts {
            int a;
            int b;
        };

        struct DerivedInts : bdlb::CStringHash {
            int a;
            int b;
        };

        struct IntsWithMember {
            bdlb::CStringHash dummy;
            int              a;
            int              b;
        };

        ASSERT(8 == sizeof(TwoInts));
        ASSERT(8 == sizeof(DerivedInts));
        ASSERT(8 < sizeof(IntsWithMember));

      } break;
      case 5: {
        // --------------------------------------------------------------------
        // TESTING BSL TRAITS
        //   The functor is an empty POD, and should have the appropriate BSL
        //   type traits to reflect this.
        //
        // Concerns:
        //: 1 The class is trivially copyable.
        //:
        //: 2 The class has the trivial default constructor trait.
        //
        // Plan:
        //: 1 ASSERT the presence of each trait required by the type. (C-1..2)
        //
        // Testing:
        //   BSL Traits
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING BSL TRAITS" << endl
                          << "==================" << endl;

        ASSERT((bsl::is_trivially_copyable<Obj>::value));
        ASSERT((bsl::is_trivially_default_constructible<Obj>::value));
      case 4: {
        // --------------------------------------------------------------------
        // STANDARD TYPEDEFS
        //   Verify that the class offers the three typedefs required of a
        //   standard adaptable binary function.
        //
        // Concerns:
        //: 1 The typedef 'argument_type' is publicly accessible and an alias
        //:   for 'const char '.
        //:
        //: 2 The typedef 'result_type' is publicly accessible and an alias for
        //:   'bool'.
        //
        // Plan:
        //: 1 ASSERT each of the typedefs has accessibly aliases the correct
        //:   type using 'bslmf::IsSame'. (C-1,2)
        //
        // Testing:
        //   typedef arguent_type
        //   typedef result_type
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "TESTING STANDARD TYPEDEFS" << endl
                          << "=========================" << endl;

        ASSERT((bslmf::IsSame<bsl::size_t,
                              bdlb::CStringHash::result_type>::VALUE));
        ASSERT((bslmf::IsSame<const char *,
                              bdlb::CStringHash::argument_type>::VALUE));

      } break;
      case 3: {
        // --------------------------------------------------------------------
        // FUNCTION CALL OPERATOR
        //   Verify that the class offers the three typedefs required of a
        //   standard adaptable binary function, ().
        //
        // Concerns:
        //: 1 Objects of type 'bdlb::CStringHash' can be invoked as a predicate
        //:   function returning 'bool' and taking a 'const char *' argument.
        //:
        //: 2 The function call operator can be invoked on constant objects.
        //:
        //: 3 The function call returns the same result as a call to
        //:   'bdlb::HashUtil::hash1' passing the argument string and its
        //:   length.
        //:
        //: 4 No memory is allocated from the default or global allocators.
        //
        // Plan:
        //: 1
        //: 2
        //: 3
        //
        // Testing:
        //   operator()(const char*, const char *) const
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "IMPLICITLY DEFINED OPERATIONS" << endl
                          << "=============================" << endl;

        if (verbose) cout <<
            "\nCreate a test allocator and install it as the default." << endl;

        bslma::TestAllocator         da("default", veryVeryVeryVerbose);
        bslma::DefaultAllocatorGuard dag(&da);

        static const struct {
            int          d_line;
            const char  *d_string;
            bsl::size_t  d_hashCode;
        } DATA[] = {
            // LINE    STRING      HASHCODE
            {  L_,     "",         0 },
            {  L_,     "AAA",      bdlb::HashUtil::hash1("AAA", 3) },
            {  L_,     "aBcXyZ!",  bdlb::HashUtil::hash1("aBcXyZ", 7) },
#if 0 // TBD Complete this table
            {  L_,     "",     "",     false,      false   },
            {  L_,     "",     "\0",   false,      false   },
            {  L_,     "",     "A",    true,       false   },
            {  L_,     "",     "z",    true,       false   },
            {  L_,     "0",    "z",    true,       false   },
            {  L_,     "1",    "",     false,      false   },
            {  L_,     "111",  "",     false,      false   },
            {  L_,     "12",   "",     false,      false   },
            {  L_,     "2",    "",     false,      false   },
            {  L_,     "A",    "",     false,      false   },
            {  L_,     "Z",    "",     false,      false   },
            {  L_,     "a",    "",     false,      false   },
            {  L_,     "z"     "",     false,      false   },
#endif
        };
        const int NUM_DATA = sizeof DATA / sizeof *DATA;

        const bdlb::CStringHash hash = bdlb::CStringHash();

        for (int i = 0; i != NUM_DATA; ++i) {
            const int          LINE      = DATA[i].d_line;
            const char        *STRING    = DATA[i].d_string;
            const bsl::size_t  HASHCODE  = DATA[i].d_hashCode;

            //LOOP_ASSERT(LINE, hash(STRING) == HASHCODE);
        }

        if (verbose) cout << "\nNegative Testing." << endl;
        {
            bsls::AssertTestHandlerGuard guard;

            ASSERT_SAFE_FAIL(hash(0));
            ASSERT_SAFE_PASS(hash("Hello world"));
        }

        LOOP_ASSERT(da.numBlocksTotal(), 0 == da.numBlocksTotal());
      } break;
      case 2: {
        // --------------------------------------------------------------------
        // IMPLICITLY DEFINED CONSTRUCTORS, DESTRUCTOR AND ASSIGNMENT OPERATOR
        //   Ensure that the four implicitly declared and defined special
        //   member functions are publicly callable and have no unexpected side
        //   effects such as allocating memory.  As there is no observable
        //   state to inspect, there is little to verify other than that the
        //   expected expressions all compile, and
        //
        // Concerns:
        //: 1 Objects can be created using the default constructor.
        //: 2 Objects can be created using the copy constructor.
        //: 3 The copy constructor is not declared as explicit.
        //: 4 Objects can be assigned to from constant objects.
        //: 5 Assignments operations can be chained.
        //: 6 Objects can be destroyed.
        //: 7 No memory is allocated by the default and global allocators.
        //
        // Plan:
        //: 1 Install a test allocator as the default allocator.  Then install
        //:   an 'AllocatorGuard' to verify no memory is allocated during the
        //:   execution of this test case.  Memory from the global allocator is
        //:   tested as a global concern. (C-7)
        //:
        //: 2 Verify the default constructor exists and is publicly accessible
        //:   by default-constructing a 'const bdlb::CStringHash' object. (C-1)
        //:
        //: 3 Verify the copy constructor is publicly accessible and not
        //:   'explicit' by using the copy-initialization syntax to create a
        //:   second 'bdlb::CStringHash' from the first. (C-2,3)
        //:
        //: 4 Assign the value of the first ('const') object to the second.
        //:   (C-4)
        //:
        //: 5 Chain the assignment of the value of the first ('const') object
        //:   to the second, into a self-assignment of the second object to
        //:   itself. (C-5)
        //:
        //: 6 Verify the destructor is publicly accessible by allowing the two
        //:   'bdlb::CStringHash' object to leave scope and be destroyed. (C-6)
        //
        // Testing:
        //   CStringHash()
        //   CStringHash(const CStringHash)
        //   ~CStringHash()
        //   CStringHash& operator=(const CStringHash&)
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "IMPLICITLY DEFINED OPERATIONS" << endl
                          << "=============================" << endl;


        if (verbose) cout <<
            "\nCreate a test allocator and install it as the default." << endl;

        bslma::TestAllocator         da("default", veryVeryVeryVerbose);
        bslma::DefaultAllocatorGuard dag(&da);

        if (verbose) cout << "Value initialization" << endl;
        const bdlb::CStringHash obj1 = bdlb::CStringHash();


        if (verbose) cout << "Copy initialization" << endl;
        bdlb::CStringHash obj2 = obj1;

        if (verbose) cout << "Copy assignment" << endl;
        obj2 = obj1;
        obj2 = obj2 = obj1;


        LOOP_ASSERT(da.numBlocksTotal(), 0 == da.numBlocksTotal());
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //   This case exercises (but does not fully test) basic functionality.
        //
        // Concerns:
        //: 1 The class is sufficiently functional to enable comprehensive
        //:   testing in subsequent test cases.
        //
        // Plan:
        //: 1 Create an object 'compare' using the default ctor.
        //:
        //: 2 Call the 'compare' functor with two string literals in lexical
        //:   order.
        //:
        //: 3 Call the 'compare' functor with two string literals in reverse
        //:   lexical order.
        //
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "BREATHING TEST" << endl
                          << "==============" << endl;

        bdlb::CStringHash hash;
        ASSERT(hash("A") > 0);

      } break;
      default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    // CONCERN: In no case does memory come from the global allocator.

    LOOP_ASSERT(globalAllocator.numBlocksTotal(),
                0 == globalAllocator.numBlocksTotal());

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