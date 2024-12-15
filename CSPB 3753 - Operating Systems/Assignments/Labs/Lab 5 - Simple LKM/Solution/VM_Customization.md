
# CSPB-3753 Lab: Accessing and Customizing your Virtual Machine
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right" style="margin-left:10px">
</figure>
<br>

We have provided you with a Ubuntu Linux Virtual Machine that is access from vSphere.  
You should have received an email that directs you to instructions and your password to access the virtual machine.
Read the [Connecting to the CS VDI Platform](https://canvas.colorado.edu/courses/64136/pages/connecting-to-the-cs-vdi-platform-vsphere) instructions and startup your VM.  Use the given password to access the VM.  The OS will make you change the password for the *student* user when you log in the first time.

<hr>

The Virtual Machine you receive is stripped down.  You need to add the packages that you will use for the assignments.  You can use NANO, VI or EMACS for editing files or you can install the VS Code development environment.

<hr>

### You need to install the following software packages:

* git
* make
* gcc-12 and linux headers
* VS Code

Commands to install the packages:

```
        sudo apt install git
        sudo apt install make 
        sudo apt install gcc
        sudo apt install linux-headers-$(uname -r)
        sudo apt install gcc-12


        # install VScode
        sudo apt-get install wget gpg
        sudo install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packagemicrosoft.gpg
        sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/packagemicrosoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sourcelist.d/vscode.list'
        sudo apt install apt-transport-https
        sudo apt update
        sudo apt install code
```

Make sure each of these commands completes succsessfuly before issuing the next request.
