--# -path=.:present:alltenses

concrete MountaineeringGer of Mountaineering = PhrasebookGer ** 
    open
      SyntaxGer,
      ParadigmsGer,
      (L = LexiconGer),
      IrregGer,
      ExtraGer,
      Prelude in {

  lin
    Mountain = mkPlace (L.mountain_N)  on_Prep zu_Prep;
    Overhang = mkPlace (mkN "�berhang" "�berh�nge" masculine) in_Prep inAcc_Prep;
    Summit = mkPlace (mkN "Gipfel") on_Prep zu_Prep;
    
    VAbseil, VRappel = mkVP (regV "abseilen");
    VBelay = mkVP (regV "sichern");
    VBoulder = mkVP (regV "bouldern");
    VClimb = mkVP (regV "klettern");
    VFall = mkVP (regV "st�rzen");
    VLead = mkVP (regV "vorsteigen");
    VStem = mkVP (regV "stemmen");
    
    GBelayOn = mkGreeting "nachkommen";
    GBelow, GRock = mkGreeting "Stein";
    GOffBelay, GSafe = mkGreeting "stand";
    GRope = mkGreeting "Seil";
    GSlack = mkGreeting "Seil";
    GUpRope = mkGreeting "Seil ein";
}
