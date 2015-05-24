import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified InfiniteString (equal)

getVars :: TC.Parser (String, String)
getVars = do s <- TC.spaces >> TC.parseString ; TC.spaces >> TC.next
             t <- TC.spaces >> TC.parseString
             return (s, t) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (s, t) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ InfiniteString.equal s t
            hClose hOut
    hClose hIn