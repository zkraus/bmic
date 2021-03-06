%global _enable_debug_package 0
%global debug_package %{nil}

Summary:            Broker Management Interface Client (BMIC)
Name:               bmic
Version:            0.0.2
Release:            1%{?dist}
License:            Apache-2.0
Group:              Development/Tools
Source:             bmic-%{version}.tar.gz
URL:                https://github.com/orpiske/bmic
BuildRequires:      cmake
BuildRequires:      make
BuildRequires:      gcc
BuildRequires:      json-c-devel
BuildRequires:      curl-devel
BuildRequires:      gru
BuildRequires:      gru-devel
Requires:           json-c
Requires:           curl
Requires:           gru


%description
This project allows access to the REST management interface exposed by brokers such as 
ActiveMQ and Artemis


%package devel
Summary:            Broker Management Interface Client (BMIC) development kit
Requires:           json-c-devel
Requires:           curl-devel
Requires:           gru-devel
Requires:           bmic
Group:              Development/Libraries

%description devel
Development packages for the BMIC

%prep
%autosetup -n bmic-%{version}

%build
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DBUILD_WITH_DOCUMENTATION=ON -DCMAKE_INSTALL_PREFIX=%{buildroot}/usr ..
make all documentation

%install
cd build
make install

%files
%doc AUTHORS README.md LICENSE COPYING
%{_bindir}/*
%{_libdir}/*


%files devel
%{_includedir}/*


%changelog
* Fri Feb 24 2017 Otavio R. Piske <angusyoung@gmail.com> - 20170224
- Initial release
