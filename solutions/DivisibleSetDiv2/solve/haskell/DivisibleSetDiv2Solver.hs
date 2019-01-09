import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified DivisibleSetDiv2 (isPossible)

getVars :: TC.Parser ([Int])
getVars = do b <- TC.spaces >> (TC.parseList TC.parseInt)
             return (b)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (b) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ DivisibleSetDiv2.isPossible b
            hClose hOut
    hClose hIn
