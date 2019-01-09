import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified BearDartsDiv2 (count)

getVars :: TC.Parser ([Int])
getVars = do w <- TC.spaces >> (TC.parseList TC.parseInt)
             return (w) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (w) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ BearDartsDiv2.count w
            hClose hOut
    hClose hIn