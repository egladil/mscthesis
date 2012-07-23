--# -path=.:present

concrete DisambMountaineeringEng of Mountaineering =
    MountaineeringEng -
      [
        PGreetingMale, PGreetingFemale,
        IMale, IFemale,
        YouFamMale, YouFamFemale, 
        YouPolMale, YouPolFemale, 
        LangNat, -- CitiNat,
        GExcuse, GExcusePol, 
        GSorry, GSorryPol, 
        GPleaseGive, GPleaseGivePol,
        GNiceToMeetYou, -- GNiceToMeetYouPol,
        PYes, PYesToNo, ObjMass,
        MKnow,
        WeMale, WeFemale,
        YouPlurFamMale, YouPlurFamFemale,
        YouPlurPolMale, YouPlurPolFemale,
        TheyMale, TheyFemale,
        PImperativeFamPos, 
        PImperativeFamNeg, 
        PImperativePolPos, 
        PImperativePolNeg,
        PImperativePlurPos,
        PImperativePlurNeg,
        
        ProBelayerMale,
        ProBelayerFemale,
        ProClimberMale,
        ProClimberFemale,
        ProLeaderMale,
        ProLeaderFemale,
        ProSecondMale,
        ProSecondFemale
      ],
    DisambPhrasebookEng -
      [
        ABusinessman,
        ACook,
        ADoctor,
        AEngineer,
        ALawyer,
        AProfessor,
        AStudent,
        ATeacher
      ] **
    open
      SyntaxEng,
      ParadigmsEng,
      IrregEng,
      Prelude in {
  lin

    ProBelayerMale = mkN "belayer (male)";
    ProBelayerFemale = mkN "belayer (female)";
    ProClimberMale = mkN "climber (male)";
    ProClimberFemale = mkN "climber (female)";
    ProLeaderMale = mkN "leader (male)";
    ProLeaderFemale = mkN "leader (female)";
    ProSecondMale = mkN "second (male)";
    ProSecondFemale = mkN "second (female)";
}
