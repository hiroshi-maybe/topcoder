import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified FilipTheFrog (countReachableIslands)

getVars :: TC.Parser ([Int], Int)
getVars = do positions <- TC.spaces >> (TC.parseList TC.parseInt) ; TC.spaces >> TC.next
             l <- TC.spaces >> TC.parseInt
             return (positions, l) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (positions, l) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ FilipTheFrog.countReachableIslands positions l
            hClose hOut
    hClose hIn