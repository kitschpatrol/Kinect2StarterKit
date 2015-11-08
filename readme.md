#Kinect 2 Starter Kit

**This kit aligns various stars for your convenience. It aggregates the dependencies and patches required to get the Kinect 2 sensor running in openFrameworks.**

-----

**November 2015 Notes:**

*I needed to delete and recreate my openFrameworks fork on github, which might have broken this repo. I've pointed the [submodule to the closest commit](https://github.com/liquidzym/openFrameworks/commit/fa04d0c3cb64f363a8e817509648353ef8758bbf) and included two patch files in /Patches to bring the openFrameworks fork associated with this repo into the correct state. I'm not even sure the fork is necessary anymore. I have yet to revise this project for OF 9.0 and VS2015, but it seems less necessary now that the Kinect 2 is better supported and there's less fuss involved in getting everything working. If anyone still feels this repo is useful then let me know and I'll make time for an update.*

-----

###Getting Started

1. Install Windows 8.1 (Boot Camp is fine if your Mac is endowed with USB 3. Virtual machines won't work.)

2. Install [Visual Studio 2013 Express](http://www.visualstudio.com/downloads/download-visual-studio-vs#d-express-windows-desktop). (Express is free, but the the beefier editions also work fine.)

3. Download and install [Git](http://git-scm.com/download/win). Say "no" to the fancy git-cheetah shell extension! It doesn't work correctly on Windows 8.

4. Install the [Kinect For Windows V2 SDK](http://www.microsoft.com/en-us/kinectforwindows/Purchase/developer-sku.aspx). This should be publicly available in July.

5. Get the repository and submodules. openFrameworks is included This might take a very long time:

		git clone --recursive https://github.com/kitschpatrol/Kinect2StarterKit.git
		
6. Plug in the Kinect and try the example included in ofxKinectV2 to make sure everything works. `\Kinect2StarterKit\ofAddons\ofxKinectV2\example-Simple\example-Simple.sln`		

###Hardware Requirements

- A Windows 8.1 PC or a (very) recent mac running Windows 8.1 via Bootcamp

- The [Kinect For Windows V2 Sensor](http://www.microsoft.com/en-us/kinectforwindows/Purchase/developer-sku.aspx) (This won't work with the Kinect bundled with your Xbox One.)

- A USB 3.0 port (Currently only USB host controllers based on Reneasas or Intel chipsets are supported. I've had luck with [this Reneasas-based SIIG PCI card](http://www.bhphotovideo.com/c/product/968543-REG/siig_ju_p40311_s1_dp_4_port_usb_3_0.html) in combination with the alpha Kinect 2 hardware.


###Project Goals

This project has two use cases in mind:

#####A shortcut to Windows-Native development
Simplify configuration for developing Windows-only openFrameworks applications that run natively and have full access to the Kinect 2's API. Help developers get up and running very quickly without having to align various repos. (Potentially helpful for workshops, classes, hackathons, etc.)


#####A no-fuss bridge to other platforms
Provide access to a subset of the Kinect 2's functionality for any OSC-compatible platform. In this case, skeleton data from the Kinect is streamed over the network via an instance of the starter kit running on a Windows machine. Since a wide-range of platforms can consume OSC, this should make it easier to work with the Kinect 2 on a Mac or mobile device.

I'd eventually like to merge this functionality into a more evolved and generic project like [openTSPS](https://github.com/labatrockwell/openTSPS).

A very simple OSC broadcaster with partial coverage of the Kinect 2 API is under development here: `\Kinect2StarterKit\ofApps\KinectV2OSC\KinectV2OSC.sln`


###Repository Structure

This repository uses a structure that might be unfamiliar to openFrameworks users. Due to the specificity of the various dependencies, both openFrameworks and the relevant addons are embedded as git submodules.

To avoid issues with nesting files that belong in the parent repository inside submodules, examples and addons are stored *outside* the root `/openFrameworks` directory. Paths and linkages have been updated accordingly, but if you try to drag one of the projects in `/ofApps` or `/ofAddons` into their usual locations inside the `/openFrameworks` directory, they will break.


###Credit

This repository just glues together a bunch of other people's great work.

- [liquidzym](https://github.com/liquidzym) added VS2013 compatibility to OF
- [Joshua Noble](https://github.com/joshuajnoble) wrote the KinectV2 plugin
