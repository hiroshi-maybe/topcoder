import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified ProblemSetsEasy (maxSets)

getVars :: TC.Parser (Int, Int, Int, Int, Int)
getVars = do e <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             eM <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             m <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             mH <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             h <- TC.spaces >> TC.parseInt
             return (e, eM, m, mH, h) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (e, eM, m, mH, h) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ ProblemSetsEasy.maxSets e eM m mH h
            hClose hOut
    hClose hIn