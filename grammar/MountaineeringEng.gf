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
    BelayStation = mkPlace "belay station" "at";
    Cliff = mkPlace "cliff" "on";
    ClimbingGym = mkPlace "climbing gym" "at";
    Glacier = mkPlace "glacier" "on";
    Mountain = mkPlace "mountain" "on";
    Overhang = mkPlace "overhang" "in";
    Summit = mkPlace "summit" "at";
    
    VAbseil = mkVP (regV "abseil");
    VBelay = mkVP (regV "belay");
    VBoulder = mkVP (regV "boulder");
    VClimb = mkVP (regV "climb");
    VFall = mkVP (regV "fall");
    VLead = mkVP (regV "lead");
    VRappel = mkVP (regV "rappel");
    VStem = mkVP (regV "stem");
    
    GBelayOn = mkGreeting "belay on";
    GBelow = mkGreeting "below";
    GClimbing = mkGreeting "climbing";
    GFalling = mkGreeting "falling";
    GOffBelay = mkGreeting "off belay";
    GRock = mkGreeting "rock";
    GRope = mkGreeting "rope";
    GSafe = mkGreeting "safe";
    GSlack = mkGreeting "slack";
    GUpRope = mkGreeting "up rope";
}
