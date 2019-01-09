import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified RandomPancakeStackDiv2 (expectedDeliciousness)

getVars :: TC.Parser ([Int])
getVars = do d <- TC.spaces >> (TC.parseList TC.parseInt)
             return (d) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (d) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ RandomPancakeStackDiv2.expectedDeliciousness d
            hClose hOut
    hClose hIn