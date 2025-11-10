#pragma once

#include <cppdotnet/System/Exception.hpp>

namespace System::IO
{

class IOException : public SystemException
{
public:
    IOException() = default;
    IOException(const IOException &) = delete;
    IOException(IOException &&) = default;
    IOException(std::string_view message) : SystemException( message ) { }
    IOException(std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) )
    {
    }

    IOException &operator =(const IOException &) = delete;
    IOException &operator =(IOException &&) = default;

    std::string_view ClassName() const override;
};

class DirectoryNotFoundException : public IOException
{
public:
    DirectoryNotFoundException() = default;
    DirectoryNotFoundException(const DirectoryNotFoundException &) = delete;
    DirectoryNotFoundException(DirectoryNotFoundException &&) = default;
    DirectoryNotFoundException(std::string_view message) : IOException( message ) { }
    DirectoryNotFoundException(std::string_view message, Exception &&inner_exception)
        :
        IOException( message, std::move(inner_exception) )
    {
    }

    DirectoryNotFoundException &operator =(const DirectoryNotFoundException &) = delete;
    DirectoryNotFoundException &operator =(DirectoryNotFoundException &&) = default;

    std::string_view ClassName() const override;
};

class EndOfStreamException : public IOException
{
public:
    EndOfStreamException() = default;
    EndOfStreamException(const EndOfStreamException &) = delete;
    EndOfStreamException(EndOfStreamException &&) = default;
    EndOfStreamException(std::string_view message) : IOException( message ) { }
    EndOfStreamException(std::string_view message, Exception &&inner_exception)
        :
        IOException( message, std::move(inner_exception) )
    {
    }

    EndOfStreamException &operator =(const EndOfStreamException &) = delete;
    EndOfStreamException &operator =(EndOfStreamException &&) = default;

    std::string_view ClassName() const override;
};

class FileNotFoundException : public IOException
{
public:
    FileNotFoundException() = default;
    FileNotFoundException(const FileNotFoundException &) = delete;
    FileNotFoundException(FileNotFoundException &&) = default;
    FileNotFoundException(std::string_view message) : IOException( message ) { }
    FileNotFoundException(std::string_view message, std::string_view filename)
        :
        IOException( message ),
        _filename{ filename }
    {
    }
    FileNotFoundException(std::string_view message, Exception &&inner_exception)
        :
        IOException( message, std::move(inner_exception) )
    {
    }
    FileNotFoundException(std::string_view message, std::string_view filename, Exception &&inner_exception)
        :
        IOException( message, std::move(inner_exception) ),
        _filename{ filename }
    {
    }

    FileNotFoundException &operator =(const FileNotFoundException &) = delete;
    FileNotFoundException &operator =(FileNotFoundException &&) = default;

    std::string_view ClassName() const override;
protected:
    std::string _filename;
};

class PathTooLongException : public IOException
{
public:
    PathTooLongException() = default;
    PathTooLongException(const PathTooLongException &) = delete;
    PathTooLongException(PathTooLongException &&) = default;
    PathTooLongException(std::string_view message) : IOException( message ) { }
    PathTooLongException(std::string_view message, Exception &&inner_exception)
        :
        IOException( message, std::move(inner_exception) )
    {
    }

    PathTooLongException &operator =(const PathTooLongException &) = delete;
    PathTooLongException &operator =(PathTooLongException &&) = default;

    std::string_view ClassName() const override;
};

}