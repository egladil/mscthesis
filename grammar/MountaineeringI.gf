incomplete concrete MountaineeringI of Mountaineering = Phrasebook ** 
    open
      Syntax,
      Lexicon,
      Symbolic,  -- for names as strings
      Prelude
    in {
  lincat
    HoldKind = CN;
    KnotKind = CN;
    Profession = N;

  lin
    KnotToKind x = x;
    
    ThisProfession pro = {name = mkNP this_Quant pro ; isPron = False ; poss = this_Quant};
    ThatProfession pro = {name = mkNP that_Quant pro ; isPron = False ; poss = that_Quant};
    TheseProfessions pro = {name = mkNP this_Quant plNum pro ; isPron = False ; poss = this_Quant};
    ThoseProfessions pro = {name = mkNP that_Quant plNum pro ; isPron = False ; poss = that_Quant};
    TheProfession pro = {name = mkNP the_Quant pro ; isPron = False ; poss = the_Quant};
    TheProfessions pro = {name = mkNP the_Quant plNum pro ; isPron = False ; poss = the_Quant};

-- Sentences
  lin
    ADoVerbPhraseDirection p vp x = mkCl p.name (mkVP vp x.to) ;
    AModVerbPhraseDirection m p vp x = mkCl p.name (mkVP m (mkVP vp x.to)) ;
    
-- Words
  lin
    V2Tie o = mkVP tie_V2 o;
    
    ProTeacherMale, ProTeacherFemale = teacher_N;
    ProPhysicianMale, ProPhysicianFemale = doctor_N;
}
