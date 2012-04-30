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
}