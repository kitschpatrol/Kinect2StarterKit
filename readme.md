#Kinect 2 Starter Kit

**This kit aligns various stars for your convenience. It aggregates the dependencies and patches required to get the Kinect 2 sensor running in openFrameworks.**



###Getting Started

1. Install Windows 8.1 (Boot Camp is fine if your Mac is endowed with USB 3. Virtual machines won't work.)

2. Install Visual Studio 2013.

3. Download and install [Git](http://git-scm.com/download/win). Say "no" to the fancy git-cheetah shell extension! It doesn't work correctly on Windows 8.

4. Install the [Kinect For Windows V2 SDK](http://www.microsoft.com/en-us/kinectforwindows/Purchase/developer-sku.aspx). This should be publicly available in July.

5. Get the repository and submodules. openFrameworks is included This might take a very long time:

		git clone --recursive git@github.com:kitschpatrol/Kinect2StarterKit.git
		
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
