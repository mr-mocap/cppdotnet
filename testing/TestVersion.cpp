#include "TestVersion.hpp"
#include "System/Version.hpp"
#include "System/Exception.hpp"
#include <iostream>
#include <cassert>


namespace TestVersion
{

void DefaultConstructed()
{
    std::cout << __func__ << std::endl;

    System::Version default_constructed;

    assert( default_constructed.Major() == 0 );
    assert( default_constructed.Minor() == 0 );
    assert( default_constructed.Build() == -1 );
    assert( default_constructed.Revision() == -1 );
}

void ConstructWithMajorAndMinor()
{
    std::cout << __func__ << std::endl;

    System::Version v{ 1, 3 };

    assert( v.Major() == 1 );
    assert( v.Minor() == 3 );
    assert( v.Build() == -1 );
    assert( v.Revision() == -1 );
}

void ConstructWithMajorAndMinorAndBuild()
{
    std::cout << __func__ << std::endl;

    System::Version v{ 1, 3, 12 };

    assert( v.Major() == 1 );
    assert( v.Minor() == 3 );
    assert( v.Build() == 12 );
    assert( v.Revision() == -1 );
}

void ConstructWithMajorAndMinorAndBuildAndRevision()
{
    std::cout << __func__ << std::endl;

    System::Version v{ 1, 3, 12, 32 };

    assert( v.Major() == 1 );
    assert( v.Minor() == 3 );
    assert( v.Build() == 12 );
    assert( v.Revision() == 32 );
}

void ConstructWithString()
{
    using namespace std::literals;

    std::cout << __func__ << std::endl;

    {
        System::Version v{ System::Version::Parse("3") };

        assert( v.Major() == 3 );
        assert( v.Minor() == 0 );
        assert( v.Build() == -1 );
        assert( v.Revision() == -1 );
    }

    // Just Major
    {
        System::Version v{ "3" };

        assert( v.Major() == 3 );
        assert( v.Minor() == 0 );
        assert( v.Build() == -1 );
        assert( v.Revision() == -1 );
    }
    
    // Major & minor
    {
        System::Version v{ "3.6" };

        assert( v.Major() == 3 );
        assert( v.Minor() == 6 );
        assert( v.Build() == -1 );
        assert( v.Revision() == -1 );
    }
    
    // Major, minor, and build
    {
        System::Version v{ "3.6.22" };

        assert( v.Major() == 3 );
        assert( v.Minor() == 6 );
        assert( v.Build() == 22 );
        assert( v.Revision() == -1 );
    }
    
    // Major, minor, build, and revision
    {
        System::Version v{ "3.6.22.127" };

        assert( v.Major() == 3 );
        assert( v.Minor() == 6 );
        assert( v.Build() == 22 );
        assert( v.Revision() == 127 );
    }
}

void ToStringWithParameter()
{
    std::cout << __func__ << std::endl;

    {
        System::Version d;

        {
            std::string s{ d.ToString(0) };

            assert( s.empty() );
        }
        {
            std::string s{ d.ToString(1) };

            assert( s == "0" );
        }
        {
            std::string s{ d.ToString(2) };

            assert( s == "0.0" );
        }

        try
        {
            std::string s{ d.ToString(3) };

            assert( s == "Shouldn't get here!" );
        }
        catch (const System::ArgumentException &e)
        {
            std::cout << e.ToString() << std::endl;
            std::cout << e.TargetSite() << std::endl;
            std::cout << std::endl;
        }
    }
}

void Run()
{
    std::cout << "Running Version Tests..." << std::endl;

    DefaultConstructed();
    ConstructWithMajorAndMinor();
    ConstructWithMajorAndMinorAndBuild();
    ConstructWithMajorAndMinorAndBuildAndRevision();
    ConstructWithString();
    ToStringWithParameter();

    std::cout << "PASSED!" << std::endl;
}

}