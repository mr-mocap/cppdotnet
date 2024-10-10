#pragma once

#include "System/Exception.hpp"

namespace System::IO
{

class IOException : public SystemException
{
public:
    IOException() = default;
    IOException(const IOException &) = delete;
    IOException(IOException &&) = default;
    IOException(const std::string_view message) : SystemException( message ) { }
    IOException(const std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, inner_exception )
    {
    }

    DirectoryIOException &operator =(const DirectoryIOException &) = delete;
    DirectoryIOException &operator =(DirectoryIOException &&) = default;
};

class DirectoryNotFoundException : public IOException
{
public:
    DirectoryNotFoundException() = default;
    DirectoryNotFoundException(const DirectoryNotFoundException &) = delete;
    DirectoryNotFoundException(DirectoryNotFoundException &&) = default;
    DirectoryNotFoundException(const std::string_view message) : SystemException( message ) { }
    DirectoryNotFoundException(const std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, inner_exception )
    {
    }

    DirectoryNotFoundException &operator =(const DirectoryNotFoundException &) = delete;
    DirectoryNotFoundException &operator =(DirectoryNotFoundException &&) = default;
};

class EndOfStreamException : public IOException
{
public:
    EndOfStreamException() = default;
    EndOfStreamException(const EndOfStreamException &) = delete;
    EndOfStreamException(EndOfStreamException &&) = default;
    EndOfStreamException(const std::string_view message) : IOException( message ) { }
    EndOfStreamException(const std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, inner_exception )
    {
    }

    EndOfStreamException &operator =(const EndOfStreamException &) = delete;
    EndOfStreamException &operator =(EndOfStreamException &&) = default;
};

class FileNotFoundException : public IOException
{
public:
    FileNotFoundException() = default;
    FileNotFoundException(const FileNotFoundException &) = delete;
    FileNotFoundException(FileNotFoundException &&) = default;
    FileNotFoundException(const std::string_view message) : IOException( message ) { }
    FileNotFoundException(const std::string_view message, const std::string_view filename)
        :
        IOException( message ),
        _filename{ filename }
    {
    }
    FileNotFoundException(const std::string_view message, Exception &&inner_exception)
        :
        IOException( message, inner_exception )
    {
    }
    FileNotFoundException(const std::string_view message, const std::string_view filename, Exception &&inner_exception)
        :
        IOException( message, inner_exception ),
        _filename{ filename }
    {
    }

    FileNotFoundException &operator =(const FileNotFoundException &) = delete;
    FileNotFoundException &operator =(FileNotFoundException &&) = default;
protected:
    std::string _filename;
};

class PathTooLongException : public IOException
{
public:
    PathTooLongException() = default;
    PathTooLongException(const PathTooLongException &) = delete;
    PathTooLongException(PathTooLongException &&) = default;
    PathTooLongException(const std::string_view message) : IOException( message ) { }
    PathTooLongException(const std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, inner_exception )
    {
    }

    PathTooLongException &operator =(const PathTooLongException &) = delete;
    PathTooLongException &operator =(PathTooLongException &&) = default;
};

}