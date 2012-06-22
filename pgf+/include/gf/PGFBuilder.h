//
//  PGFBuilder.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__PGFBuilder_h
#define pgf__PGFBuilder_h

#include <stdio.h>
#include <string>

#include <gf/PGF.h>

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
        static const PGF& fromFile(const std::string& filename);
        
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
        static const PGF& fromFile(const std::string& filename, const std::vector<std::string>& languages);
        
        /**
         * Reads a pgf from an input stream
         *
         * @param stream a c input stream to read the pgf binary from.
         * @return the read pgf object
         * @throws gf::IOException if the file could not be read
         */
        static const PGF& fromStdIOStream(FILE* stream);
        
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
        static const PGF& fromStdIOStream(FILE* stream, const std::vector<std::string>& languages);
    };
    
}

#endif
