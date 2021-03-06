//
//  AlternToksSymbol.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__AlternToksSymbol_h
#define pgf__AlternToksSymbol_h

#include <vector>
#include <gf/reader/Alternative.h>
#include <gf/reader/ToksSymbol.h>

namespace gf {
    namespace reader {
        
        class AlternToksSymbol : public ToksSymbol {
        private:
            std::vector<Alternative*> alternatives;
            
        public:
            /**
             * Create an AlternToksSymbol object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            AlternToksSymbol(const std::vector<std::string>& tokens, const std::vector<Alternative*>& alternatives);
            virtual ~AlternToksSymbol();
            
            virtual const std::vector<Alternative*>& getAlternatives() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
