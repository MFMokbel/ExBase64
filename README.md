# ExBase64

ExBase64 is a Base64 encoding and decoding command line tool that leverages the full capabilities of [**Base64CPPLib**](https://github.com/MFMokbel/Base64CPPLib) Library. It attempts to explore and demonstrate, almost, every API of the library in a standardized fashion.

# Code

Other than the dependency on the [**Base64CPPLib**](https://github.com/MFMokbel/Base64CPPLib) Library, the code comes with a ***driver*** class that calls into said library and exposes different features of it. Moreover, the ***driver*** class has no OS or other dependencies.

# Tool Screenshot (-h option)

![Options Available](/screenshots/Base64_help.JPG)

# Usage

The tool is very liberal in terms of parsing command line arguments such that whenever an argument match is encountered, it consumes it as it is. Each standalone option could be placed anywhere; the order is not enforced. Moreover, any option used in a non-matching scenario, will be ignored.



**Note**: When encoding ***-ef*** or decoding ***-df*** a file, if the option ***-o*** is not specified, results will be printed to the console window.

# Examples

1. To encode a string 2 times, with a custom padding character "*", and a custom alphabet (substitution) table "23456789APQRSTUVW@#$abcdefghijk~!0mnopqrstuvwxy^&CDEFGHIJKLMNO()"

```
ExBase64 -e:s "hello world" -t 2 -p * -s "23456789APQRSTUVW@#$abcdefghijk~!0mnopqrstuvwxy^&CDEFGHIJKLMNO()"

Output: fE0mjH!J$m7u#6O6g50dQ!**
```
2. If you want to print/return the output as hexadecimal stream, you use the ***-r:h*** option, and if you want it delimited as well, you use the option ***-dl:o*** <*delimiter*>

```
ExBase64 -e:s "hello world" -r:h -dl:o :

Output: 61:47:56:73:62:47:38:67:64:32:39:79:62:47:51:3D
```
3. If you want to encode/decode hex delimited data straight from the command line, you use the option ***-e:h*** for encoding, and ***-d:h*** for decoding, and the option ***-dl:i*** <*delimiter*> to tell the parser that given hexadecimal stream is delimited with whatever delimiter. for example,

```
ExBase64 -d:h 61:47:56:73:62:47:38:67:64:32:39:79:62:47:51:3D -dl:i :

Output: hello world
```

# Binaries

Although the code has no OS depdendency, I'm only releasing Windows 32-bit and 64-bit executables. It should be a straightforward task to compile it for other OSes. Binaries are located under the **Release** folder.

# Requirements

The only requirement is a C++ compiler with support for C++11 and C++14.

# Contributing

Open for pull requests and issues. Comments and suggestions are greatly appreciated.
