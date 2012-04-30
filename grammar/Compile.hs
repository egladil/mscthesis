import List
import System

-- (c) Aarne Ranta 2010 under GNU LGPL

-- Compile files into pgf, in chosen combinations.

-- Usage: runghc Compile (-make | -link)? Eng Fre Fin ...
-- The -make option links all pgf files to one in the end
-- The -link option only links, without first compiling
-- Arguments whose length are 3 characters are prefixed with mainmodu.
-- Other arguments are passed literally.

-- Thus, for instance, to produce an English-Swedish-Romanian phrasebook with English
-- disambiguation, the command is
--
--  runghc Compile -link Eng Swe Ron DisambPhrasebookEng


-- change this to apply to another project; alternatively, just use full file names
mainmodu = "Mountaineering"

main = do
  (opts,langs) <- getArgs >>= return . partition ((=='-') . head)
  let modus = [mkFile la | la <- langs]
  let opt = elem "-opt" opts
  putStrLn $ unwords modus
  if notElem "-link" opts 
    then mapM_ (compileOne opt) modus >> return ()
    else return ()
  case opts of
    _ | elem "-make" opts || elem "-link" opts -> do
      let comm = "gf -i ../GF/examples/phrasebook -make -s " ++ unwords (map (++ ".pgf") modus)
      putStrLn comm
      system comm
      return () 
    _ -> return ()

compileOne opt modu = do
  let optim = if opt then " -optimize-pgf" else ""
      comm = "gf -i ../GF/examples/phrasebook -make -s" ++ optim ++ " -name=" ++ 
             modu ++ " " ++ modu ++ ".gf" ++
             " +RTS -K32M"
  putStrLn comm
  system comm

mkFile la = if length la == 3 then mainmodu ++ la else la
