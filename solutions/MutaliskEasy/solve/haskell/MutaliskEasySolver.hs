import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified MutaliskEasy (minimalAttacks)

getVars :: TC.Parser ([Int])
getVars = do x <- TC.spaces >> (TC.parseList TC.parseInt)
             return (x) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (x) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ MutaliskEasy.minimalAttacks x
            hClose hOut
    hClose hIn