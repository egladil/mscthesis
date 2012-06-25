//
//  Concrete.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Concrete_h
#define pgf__Concrete_h

#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <set>

#include <gf/reader/CncCat.h>
#include <gf/reader/CncFun.h>
#include <gf/reader/Production.h>
#include <gf/reader/ProductionSet.h>
#include <gf/reader/RLiteral.h>
#include <gf/reader/Sequence.h>

namespace gf {
    namespace reader {
        
        class Concrete {
        private:
            std::string name;
            std::map<std::string, RLiteral*> flags;
            std::vector<Sequence*> seqs;
            std::vector<CncFun*> cncFuns;
            std::vector<ProductionSet*> prods;
            std::map<std::string, CncCat*> cncCats;
            int32_t fId;
            /* final */ std::string startCat;
            
        public:
            Concrete(const std::string& name, const std::map<std::string, RLiteral*>& flags, const std::vector<Sequence*>& seqs, const std::vector<CncFun*>& cncFuns, const std::vector<ProductionSet*>& prods, const std::map<std::string, CncCat*>& cncCats, int32_t fId, const std::string& startCat);
            virtual ~Concrete();
            
            virtual const std::string& getName() const;
            
            /**
             * returns the concretes categories (forest indices) corresponding to the
             * given abstract category.
             * @param absCat the name of the abstract category
             * @return the CncCat object
             * @throws gf::UnknownCategoryException if the category is unknown
             **/
            virtual CncCat& concreteCat(const std::string& absCat);
            virtual const CncCat& concreteCat(const std::string& absCat) const;
            
            virtual const std::vector<Sequence>& getSequences() const;
            virtual const std::vector<CncFun>& getCncFuns() const;
            virtual const std::vector<ProductionSet>& getProductionSets() const;
            
            // TODO: Cache vector?
            virtual std::vector<CncCat> getCncCats() const;
            
            virtual int32_t getFId() const;
            virtual const CncCat& getStartCat() const;
          
            // TODO: Cache vector?
            virtual std::vector<Production> productions() const;
            
            virtual std::string toString() const;
            
            // TODO: Cache map?
            virtual std::map<int32_t, std::set<Production> > getSetOfProductions() const;
        };
        
    }
}

#endif
