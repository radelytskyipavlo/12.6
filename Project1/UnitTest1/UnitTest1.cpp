#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
    TEST_CLASS(LastPassengerProbabilityTest)
    {
    public:

        TEST_METHOD(ProbabilityInRangeTest)
        {
            Elem* first = nullptr;
            Elem* last = nullptr;
            read(first, last);

            float probability = lastPassengerProbability(first);

            freeMemory(first, last);

            Assert::IsTrue(probability >= 0 && probability <= 1);
        }
    };
}