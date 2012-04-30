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
    
    GBelayOn = mkGreeting "belay on";
    GBelow = mkGreeting "below";
    GFalling = mkGreeting "falling";
    GOffBelay = mkGreeting "off belay";
    GRock = mkGreeting "rock";
    GRope = mkGreeting "rope";
    GSafe = mkGreeting "safe";
    GSlack = mkGreeting "slack";
    GUpRope = mkGreeting "up rope";
}
