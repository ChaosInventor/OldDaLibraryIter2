#ifndef DEBUG__DEBUG_DEBUG_HPP
#define DEBUG__DEBUG_DEBUG_HPP

#ifdef LIBRARY_DEBUG

#define IfLibraryDebugDo(p_expression) p_expression

    //TODO: Is this okay?
    #include <iostream>

#else

    #define IfLibraryDebugDo(p_expression)

#endif //LIBRARY_DEBUG


#define Warn(p_msg) IfLibraryDebugDo(std::cerr << "[Warning(" << __FILE__ << ":" << __LINE__ << ")]:" << p_msg << "\n";)
#define Error(p_msg) IfLibraryDebugDo(std::cerr << "[Error(" << __FILE__ << ":" << __LINE__ << ")]:" << p_msg << "\nAborting...\n"; abort();)

#define Check(p_statement, p_msg) IfLibraryDebugDo(if(!(p_statement)){ Warn("Failed check { " << #p_statement << " } With message:\n\t" << p_msg) })
#define Assert(p_statement, p_msg) IfLibraryDebugDo(if(!(p_statement)){ Error("Failed assertion { " << #p_statement << " } With message:\n\t" << p_msg) })

#define Assume(p_statement) Assert((p_statement), "This function assumes that this is true, if it is false(like now) then it's behaviour is undefined.");

//TODO: How do I even implement these?
#define ValidateMemoryRangeReadability(p_location, p_bytes) Warn("Cannot confirm the readability of bytes at " (p_location) << " going on for " << (p_bytes) << " bytes")
#define ValidateMemoryRangeWritability(p_location, p_bytes) Warn("Cannot confirm the writability of bytes at " (p_location) << " going on for " << (p_bytes) << " bytes")
#define ValidateMemoryRangeExecutability(p_location, p_bytes) Warn("Cannot confirm the executability of bytes at " (p_location) << " going on for " << (p_bytes) << " bytes")

#endif //DEBUG__DEBUG_DEBUG_HPP