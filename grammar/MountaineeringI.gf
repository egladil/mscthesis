incomplete concrete MountaineeringI of Mountaineering = Phrasebook ** 
    open
      Syntax,
      Lexicon,
      Symbolic,  -- for names as strings
      Prelude
    in {
  lincat
    Hold = CN;
    KnotKind = CN;

  lin
    KnotToKind x = x;

-- Sentences
  lin
    ADoVerbPhraseDirection p vp x = mkCl p.name (mkVP vp x.to) ;
    AModVerbPhraseDirection m p vp x = mkCl p.name (mkVP m (mkVP vp x.to)) ;
    
-- Words
  lin
    V2Tie o = mkVP tie_V2 o;
}
