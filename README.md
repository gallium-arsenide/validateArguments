# validateArguments output

----------------------------------
Input:
Output: -1
----------------------------------
----------------------------------
Input: ""
Output: -1
----------------------------------
----------------------------------
Input: "--help"
Output: 1
----------------------------------
----------------------------------
Input: "--hElP"
Output: 1
----------------------------------
----------------------------------
Input: "--help invalid"
Output: -1
----------------------------------
----------------------------------
Input: "--name" "SOME_NAME"
Output: 0
----------------------------------
----------------------------------
Input: "--name" "s"
Output: -1
----------------------------------
----------------------------------
Input: "--name" "to long name so invalid"
Output: -1
----------------------------------
----------------------------------
Input: "--count" "5"
Output: 0
----------------------------------
----------------------------------
Input: "--count" "-2"
Output: -1
----------------------------------
----------------------------------
Input: "--count" "13"
Output: -1
----------------------------------
----------------------------------
Input: "--count" "invalid"
Output: -1
----------------------------------
----------------------------------
Input: "--name" "SOME_NAME" "--count" "10"
Output: 0
----------------------------------
----------------------------------
Input: "--name" "SOME_NAME" "--count" "10" "--help"
Output: 1
----------------------------------