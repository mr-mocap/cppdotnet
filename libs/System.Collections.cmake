add_library(cppdotnet_collections)

# set C++ standard for this target from the option
set_target_properties(cppdotnet_base PROPERTIES
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_sources(cppdotnet_collections
        PRIVATE
            src/cppdotnet/System/Collections/Generic/Dictionary.cpp
            src/cppdotnet/System/Collections/Generic/HashSet.cpp
            src/cppdotnet/System/Collections/Generic/ICollection.cpp
            src/cppdotnet/System/Collections/Generic/IDictionary.cpp
            src/cppdotnet/System/Collections/Generic/IList.cpp
            src/cppdotnet/System/Collections/Generic/KeyNotFoundException.cpp
            src/cppdotnet/System/Collections/Generic/KeyValuePair.cpp
            src/cppdotnet/System/Collections/Generic/LinkedList.cpp
            src/cppdotnet/System/Collections/Generic/List.cpp
            src/cppdotnet/System/Collections/Generic/OrderedDictionary.cpp
            src/cppdotnet/System/Collections/Generic/SortedDictionary.cpp
            src/cppdotnet/System/Collections/Generic/SortedSet.cpp
            src/cppdotnet/System/Collections/Generic/Stack.cpp
            src/cppdotnet/System/Collections/Specialized/StringCollection.cpp
            src/cppdotnet/System/Collections/Specialized/StringDictionary.cpp
               
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/cppdotnet/System/Collections/Generic.hpp
            include/cppdotnet/System/Collections/Specialized.hpp
            include/cppdotnet/System/Collections/Generic/Concepts.hpp
            include/cppdotnet/System/Collections/Generic/Dictionary.hpp
            include/cppdotnet/System/Collections/Generic/HashSet.hpp
            include/cppdotnet/System/Collections/Generic/ICollection.hpp
            include/cppdotnet/System/Collections/Generic/IDictionary.hpp
            include/cppdotnet/System/Collections/Generic/IList.hpp
            include/cppdotnet/System/Collections/Generic/KeyNotFoundException.hpp
            include/cppdotnet/System/Collections/Generic/KeyValuePair.hpp
            include/cppdotnet/System/Collections/Generic/LinkedList.hpp
            include/cppdotnet/System/Collections/Generic/List.hpp
            include/cppdotnet/System/Collections/Generic/OrderedDictionary.hpp
            include/cppdotnet/System/Collections/Generic/Private.hpp
            include/cppdotnet/System/Collections/Generic/SortedDictionary.hpp
            include/cppdotnet/System/Collections/Generic/SortedSet.hpp
            include/cppdotnet/System/Collections/Generic/Stack.hpp
            include/cppdotnet/System/Collections/Generic/Private/ICollectionInterface.hpp
            include/cppdotnet/System/Collections/Generic/Private/IDictionaryInterface.hpp
            include/cppdotnet/System/Collections/Generic/Private/IListInterface.hpp
            include/cppdotnet/System/Collections/Generic/Private/LegacyBidirectionalIterator.hpp
            include/cppdotnet/System/Collections/Generic/Private/LegacyForwardIterator.hpp
            include/cppdotnet/System/Collections/Generic/Private/LegacyRandomAccessIterator.hpp
            include/cppdotnet/System/Collections/Specialized/StringCollection.hpp
            include/cppdotnet/System/Collections/Specialized/StringDictionary.hpp
)