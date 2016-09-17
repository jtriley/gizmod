# -*- mode: Shell-script; indent-tabs-mode: t; tab-width: 4; … -*-
# Copyright 1999-2016 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Id$

EAPI=6

inherit git-r3 eutils cmake-utils

DESCRIPTION="Input event scripting utility that has special support for fancy keyboards and mice, USB dials, LIRC and USB remotes, and more."
HOMEPAGE="http://gizmod.sourceforge.net"
EGIT_REPO_URI="https://github.com/bb010g/${PN}.git"

LICENSE="Apache-2.0"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE="libvisual"

RDEPEND="x11-libs/libX11
	dev-lang/python
	media-libs/alsa-lib
	>=dev-libs/boost-1.46.0
	libvisual? ( >=media-libs/libvisual-0.4.0 )"
DEPEND="${RDEPEND}
	x11-proto/xproto"

src_configure() {
	local mycmakeargs=(
		-DBUILD_VIS_PLUGIN="$(usex libvisual)"
	)

	cmake-utils_src_configure
}
