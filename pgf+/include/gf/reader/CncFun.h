//
//  CncFun.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__CncFun_h
#define pgf__CncFun_h

#include <stdint.h>
#include <string>
#include <vector>

#include <gf/RefBase.h>
#include <gf/reader/Sequence.h>
#include <gf/reader/Symbol.h>

namespace gf {
    namespace reader {
        
        class CncFun : public gf::RefBase {
        private:
            std::string name;
            std::vector<Sequence*> sequences;
            
        public:
            /**
             * Create a CncFun object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            CncFun(const std::string& name, const std::vector<Sequence*>& sequences);
            virtual ~CncFun();
            
            virtual const std::string& getName() const;
            
            virtual const std::vector<Sequence*>& getSequences() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
