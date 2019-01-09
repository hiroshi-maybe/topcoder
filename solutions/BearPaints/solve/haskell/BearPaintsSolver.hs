import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified BearPaints (maxArea)

getVars :: TC.Parser (Int, Int, Integer)
getVars = do w <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             h <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             m <- TC.spaces >> TC.parseLong
             return (w, h, m) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (w, h, m) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ BearPaints.maxArea w h m
            hClose hOut
    hClose hIn