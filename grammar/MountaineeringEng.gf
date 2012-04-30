--# -path=.:present:alltenses

concrete MountaineeringEng of Mountaineering = PhrasebookEng **
    open 
      SyntaxEng, 
      ParadigmsEng, 
      (L = LexiconEng), 
      (P = ParadigmsEng), 
      IrregEng, 
      ExtraEng, 
      Prelude in {

  lin
    Mountain = mkPlace "mountain" "at";
    Overhang = mkPlace "overhang" "in";
    Summit = mkPlace "summit" "at";
}
