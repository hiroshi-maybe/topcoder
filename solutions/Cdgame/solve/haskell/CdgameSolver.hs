import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified Cdgame (rescount)

getVars :: TC.Parser ([Int], [Int])
getVars = do a <- TC.spaces >> (TC.parseList TC.parseInt) ; TC.spaces >> TC.next
             b <- TC.spaces >> (TC.parseList TC.parseInt)
             return (a, b) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (a, b) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ Cdgame.rescount a b
            hClose hOut
    hClose hIn