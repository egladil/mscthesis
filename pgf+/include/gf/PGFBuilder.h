//
//  PGFBuilder.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__PGFBuilder_h
#define pgf__PGFBuilder_h

#include <stdio.h>
#include <string>

#include <gf/IOException.h>
#include <gf/PGF.h>
#include <gf/UnknownLanguageException.h>

namespace gf {
    
    class PGFBuilder {
    private:
        static const bool DBG = false;
        
        PGFBuilder();
        virtual ~PGFBuilder();
        
    public:
        /**
         * Reads a PGF binary from a file identified by filename.
         *
         * @param filename the path of the pgf file.
         * @return the read pgf object
         * @throws gf::IOException if the file could not be read
         */
        static PGF* fromFile(const std::string& filename) throw (IOException);
        
        /**
         * Reads a PGF binary from a file idenfied by filename.
         * A list of the desired languages is given to the function so that the pgf
         * doesn't have to be read entierely. The pgf file have to be indexed
         * 
         *
         * @param filename the path of the pgf file.
         * @param languages the list of desired languages
         * @return the read pgf object
         * @throws gf::IOException if the file could not be read
         * @throws gf::UnknownLanguageException if one or more of the specified languages does not exist
         */
        static PGF* fromFile(const std::string& filename, const std::set<std::string>& languages) throw (IOException, UnknownLanguageException);
        
        /**
         * Reads a pgf from an input stream
         *
         * @param stream a c input stream to read the pgf binary from.
         * @return the read pgf object
         * @throws gf::IOException if the file could not be read
         */
        static PGF* fromStdIOStream(FILE* stream) throw (IOException);
        
        /**
         * Reads a pgf from an input stream
         * A list of the desired languages is given to the function so that the pgf
         * doesn't have to be read entirely. The pgf file have to be indexed
         *
         * @param stream a c input stream to read the pgf binary from.
         * @param languages the list of desired languages
         * @return the read pgf object
         * @throws gf::IOException if the file could not be read
         * @throws gf::UnknownLanguageException if one or more of the specified languages does not exist
         */
        static PGF* fromStdIOStream(FILE* stream, const std::set<std::string>& languages) throw (IOException, UnknownLanguageException);
    };
    
}

#endif
