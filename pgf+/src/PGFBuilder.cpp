//
//  PGFBuilder.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-27.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <errno.h>
#include <stdio.h>
#include <gf/IOException.h>
#include <gf/PGFBuilder.h>
#include <gf/PGFReader.h>

namespace gf {
    
    PGF* PGFBuilder::fromFile(const std::string& filename) throw (IOException) {
        FILE* file;
        PGF* ret;
        
        file = fopen(filename.c_str(), "rb");
        if (file == NULL) {
            throw IOException(errno);
        }
        
        try {
            ret = fromStdIOStream(file);
        } catch (Exception& e) {        
            fclose(file);
            throw;
        }
        
        fclose(file);
        
        return ret;
    }
    
    PGF* PGFBuilder::fromFile(const std::string& filename, const std::set<std::string>& languages) throw (IOException, UnknownLanguageException) {
        FILE* file;
        PGF* ret;
        
        file = fopen(filename.c_str(), "rb");
        if (file == NULL) {
            throw IOException(errno);
        }
        
        try {
            ret = fromStdIOStream(file, languages);
        } catch (Exception& e) {        
            fclose(file);
            throw;
        }
        
        fclose(file);
        
        return ret;
    }
    
    PGF* PGFBuilder::fromStdIOStream(FILE* stream) throw (IOException) {
        return PGFReader(stream).readPGF();
    }
    
    PGF* PGFBuilder::fromStdIOStream(FILE* stream, const std::set<std::string>& languages) throw (IOException, UnknownLanguageException) {
        return PGFReader(stream, languages).readPGF();
    }
}