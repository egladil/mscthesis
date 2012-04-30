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
    BelayStation = mkPlace (mkN "Standplatz" "Standplätze" masculine) on_Prep zu_Prep;
    Cliff = mkPlace (mkN "Fels" "Felsen" masculine) on_Prep zu_Prep;
    ClimbingGym = mkPlace (mkN "Kletterhalle" "Kletterhallen" feminine) in_Prep inAcc_Prep;
    Glacier = mkPlace (mkN "Gletscher") on_Prep zu_Prep;
    Mountain = mkPlace (L.mountain_N) on_Prep zu_Prep;
    Overhang = mkPlace (mkN "Überhang" "Überhänge" masculine) in_Prep inAcc_Prep;
    Summit = mkPlace (mkN "Gipfel") on_Prep zu_Prep;
    
    VAbseil, VRappel = mkVP (regV "abseilen");
    VBelay = mkVP (regV "sichern");
    VBoulder = mkVP (regV "bouldern");
    VClimb = mkVP (regV "klettern");
    VFall = mkVP (regV "stürzen");
    VLead = mkVP (regV "vorsteigen");
    VStem = mkVP (regV "stemmen");
    
    GBelayOn = mkGreeting "nachkommen";
    GBelow, GRock = mkGreeting "Stein";
    GClimbing = mkGreeting "komme";
    GOffBelay, GSafe = mkGreeting "stand";
    GRope = mkGreeting "Seil";
    GSlack = mkGreeting "Seil";
    GUpRope = mkGreeting "Seil ein";
}
