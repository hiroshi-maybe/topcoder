import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified PublicTransit (minimumLongestDistance)

getVars :: TC.Parser (Int, Int)
getVars = do r <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             c <- TC.spaces >> TC.parseInt
             return (r, c) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (r, c) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ PublicTransit.minimumLongestDistance r c
            hClose hOut
    hClose hIn