import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified SquareScoresDiv2 (getscore)

getVars :: TC.Parser (String)
getVars = do s <- TC.spaces >> TC.parseString
             return (s) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (s) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ SquareScoresDiv2.getscore s
            hClose hOut
    hClose hIn