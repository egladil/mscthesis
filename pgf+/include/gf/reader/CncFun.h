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

#include <gf/reader/Sequence.h>
#include <gf/reader/Symbol.h>

namespace gf {
    namespace reader {
        
        class CncFun {
        private:
            std::string name;
            std::vector<Sequence> sequences;
            
        public:
            CncFun(const std::string& name, const std::vector<Sequence>& sequences);
            virtual ~CncFun();
            
            virtual const std::string& name() const;
            
            virtual const std::vector<Sequence>& sequences() const;
            
            virtual Sequence& sequence(uint32_t index);
            virtual const Sequence& sequence(uint32_t index) const;
            
            virtual Symbol& symbol(uint32_t seqIndex, uint32_t symbIndex);
            virtual const Symbol& symbol(uint32_t seqIndex, uint32_t symbIndex) const;
            
            virtual uint32_t size() const;
            
            virtual std::string toString() const;
        }
        
    }
}

#endif
