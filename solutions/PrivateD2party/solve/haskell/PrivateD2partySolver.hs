import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified PrivateD2party (getsz)

getVars :: TC.Parser ([Int])
getVars = do a <- TC.spaces >> (TC.parseList TC.parseInt)
             return (a) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (a) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ PrivateD2party.getsz a
            hClose hOut
    hClose hIn